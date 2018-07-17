// C++ Program to have a logic where there can be max MAXNODES objects of a
// class type node possible in the program. There is a thread which generates
// the nodes from 1 to MAXNODES and keeps it in a hash and LRU list. MAXTHREADS
// number of threads randomly does lookup of a node where it does some work
// on/using that node. A LRU thread goes through LRU list and if number of
// nodes are above a THRESHOLD, it picks one by one node from front and tries
// to delete the node. There should not be any user of node when it is being
// thrown away from LRU (and hash).
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/unordered_map.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/pthread/condition_variable_fwd.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>


using namespace std;

#define MAXNODES 20000
#define THRESHOLD (MAXNODES / 2)
#define MAXTHREADS 100

class node;

typedef boost::intrusive::list_base_hook <boost::intrusive::link_mode<
        boost::intrusive::auto_unlink> >              auto_unlink_hook;
typedef boost::intrusive::list<node,
        boost::intrusive::constant_time_size<false> > NodeList;
typedef boost::unordered_map <int, node*>             HashType;
typedef boost::intrusive_ptr <node>                   nodePtr;

class node:
    public boost::noncopyable,
    public auto_unlink_hook
{
public:
    void _init();
    node():refCnt(0),inodeNo(99199)
    {
        // cout << "node constructor" << endl;
        _init();
    }
    node(int iNo):refCnt(0),inodeNo(iNo)
    {
        // cout << "node constructor 1" << endl;
        _init();
    }
    
    ~node();
    int inodenumber() { return inodeNo; }
    void specialLock();
    void specialUnlock();
    bool isSpecialLocked() const { return mSpecialBit;}

    boost::detail::atomic_count refCnt;
private:
    int inodeNo;
    uint32_t mSpecialBit : 1;
    uint32_t mWaitSpecialBit:1;
    uint32_t mReserved:30;
};

// LRU list
NodeList nodeLRUList;

// Mutex protecting LRU insert/delete operations
boost::mutex nodeLRUMutex;

// Current node count
boost::detail::atomic_count nodeCount(0);

// Hash to hold valid nodes
HashType nodeHash;

// Mutex to protect hash
boost::mutex nodeHashMutex;

boost::condition_variable    specialCV;

// Shutdown flag
volatile bool shutdown = false;

void node::specialLock()
{
    boost::unique_lock<boost::mutex> hashLock(nodeHashMutex);

    while (mSpecialBit)
    {
        mWaitSpecialBit = 1;
        specialCV.wait(hashLock);
    }

    mSpecialBit = 1;
}

void node::specialUnlock()
{
    boost::unique_lock<boost::mutex> hashLock(nodeHashMutex);

    mSpecialBit = 0;
    if (mWaitSpecialBit)
    {
        mWaitSpecialBit = 0;
        specialCV.notify_all();
    }
}

bool findNodeInHash(int INo, nodePtr& node, bool log = false)
{
    {
        boost::mutex::scoped_lock lock(nodeHashMutex);
        HashType::iterator it = nodeHash.find(INo);
        if (it != nodeHash.end()) {
            node.reset(it->second);
            if (log)
                cout << "node of ino " << INo << " found ref " << node->refCnt << endl;
            return true;
        }
    }

    if (log)
        cout << "node of ino " << INo << " not found" << endl;
    return false;
}

void cleanupHash()
{
    boost::mutex::scoped_lock lock(nodeHashMutex);
    while (!nodeHash.empty()) {
        HashType::iterator it = nodeHash.begin();
        // cout << "SNB cleaning hash inode " << it->second->inodenumber() << endl;
        // nodeHash.erase(it->second->inodenumber());
        delete it->second;
    }
}

void node::_init()
{
    {
        boost::mutex::scoped_lock lock(nodeHashMutex);
        // cout << "Added " << this->inodeNo << " to hash" << endl;
        nodeHash.insert(HashType::value_type(this->inodeNo, this));
    }
    ++nodeCount;
}

node::~node()
{
    // cout << "node destructor inode " << inodenumber() << endl;
    --nodeCount;
    nodeHash.erase(this->inodeNo);
}

void intrusive_ptr_add_ref(node *n)
{
    boost::mutex::scoped_lock lock(nodeLRUMutex);
    // int a = ++n->refCnt;
    // if (a == 1) {
    //     cout << n->inodenumber() << " intrusive_ptr_add_ref " << a << endl;
    if (++n->refCnt == 1) {
        n->auto_unlink_hook::unlink();
        cout << n->inodenumber() << " intrusive_ptr_add_ref " << 1 << endl;
    }
}

void intrusive_ptr_release(node *n)
{
    boost::mutex::scoped_lock lock(nodeLRUMutex);
    if (0 == --n->refCnt) {
        cout << n->inodenumber() << " intrusive_ptr_release " << n->refCnt << endl;
        nodeLRUList.push_back(*n);
    }
}

void random_io_thread(int threadNo)
{
    int i = 1;
    while (!shutdown)
    {
        nodePtr node;
        bool found = findNodeInHash(i, node);
        if (found)
        {
            // Use it for some time
            cout << "Using inode " << i << " ref " << node->refCnt << " by thread " << threadNo << endl;
        }
        // boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * threadNo));
        if (++i > MAXNODES)
            i = 1;
    }

    cout << "Exiting thread " << threadNo << endl;
}

void prepareNodes()
{
    int i = 1;
    while (!shutdown) {
        nodePtr node1;
        if (findNodeInHash(i, node1) == false) {
            // cout << "need to add a node " << i << " to hash" << endl;
            boost::intrusive_ptr <node> A =  new node(i);
        }
        if (++i > MAXNODES) {
            i = 1;break;}
        // boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

void collapseNode(node &node)
{
    if (node.refCnt >  1) {
        // cout << "SNB some other thread has taken ref on node " << node.inodenumber() << endl;
        goto abort;
    }
    {
        boost::mutex::scoped_lock lock(nodeHashMutex);

        if (node.refCnt >  1) {
            // cout << "SNB some other thread has taken ref on node after hash lock " << node.inodenumber() << endl;
            goto abort;
        }
    }

    delete &node;

    return;
 abort:
    intrusive_ptr_release(&node);
}

void lruThread()
{
    node *frontNode = NULL;
    while (!shutdown) {
        if (nodeCount <= THRESHOLD) {
            boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
            continue;
        }

        {
            boost::mutex::scoped_lock lock(nodeLRUMutex);
            frontNode = &nodeLRUList.front();
            // cout << "SNB node at front is " << frontNode->inodenumber() << " ref " << frontNode->refCnt << " nodecount " << nodeCount << endl;
            nodeLRUList.pop_front();
            ++frontNode->refCnt;
        }
        if (frontNode)
            collapseNode(*frontNode);
    }
}

int main ()
{
    int i;
    boost::scoped_ptr<boost::thread>        mThreads[MAXTHREADS];
    for (i = 0; i < MAXTHREADS; i++) {
        mThreads[i].reset(new boost::thread(boost::bind(&random_io_thread,
                                                     i + 1)));
    }

    boost::scoped_ptr<boost::thread>        mThreadp;
    mThreadp.reset(new boost::thread(boost::bind(&prepareNodes)));

    boost::scoped_ptr<boost::thread>        mLRUThreadp;
    mLRUThreadp.reset(new boost::thread(boost::bind(&lruThread)));

    boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
    shutdown = true;
    for (i = 0; i < MAXTHREADS; i++) {
        mThreads[i]->join();
        mThreads[i].reset();
    }
    mThreadp->join();
    mLRUThreadp->join();
    mThreadp.reset();
    mLRUThreadp.reset();
    cleanupHash();

    return 0;
}
