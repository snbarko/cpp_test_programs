#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/intrusive_ptr.hpp>
#include    <boost/intrusive/list.hpp>
#include    <boost/noncopyable.hpp>
#include    <boost/scoped_ptr.hpp>
#include    <boost/thread/mutex.hpp>
#include    <boost/thread/thread.hpp>
#include <boost/unordered_map.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

using namespace std;

#define MAXNODES 10
#define THRESHOLD (0.5 * MAXNODES)
typedef boost::intrusive::list_base_hook<
    boost::intrusive::link_mode<
        boost::intrusive::auto_unlink> >            auto_unlink_hook;
 
class node:
    public boost::noncopyable,
    public auto_unlink_hook
{
public:
    void _init();
    node():inodeNo(99199),refCnt(0)
    {
        cout << "node constructor" << endl;
        _init();
    }
    node(int iNo):inodeNo(iNo),refCnt(0)
    {
        // cout << "node constructor 1" << endl;
        _init();
    }
    
    ~node();
    int inodenumber() { return inodeNo; }
private:
    int inodeNo;
public:
    int refCnt;
};

typedef boost::intrusive::list<node,
                               boost::intrusive::constant_time_size<false> >       NodeList;
NodeList nodeLRUList;
boost::mutex nodeLRUMutex;
int nodeCount;
typedef boost::unordered_map<int, node*>       HashType;
typedef boost::intrusive_ptr <node> nodePtr;
HashType nodeHash;
boost::mutex nodeHashMutex;
volatile bool shutdown = false;

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
        nodeHash.erase(it->second->inodenumber());
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
    {
        boost::mutex::scoped_lock lock(nodeLRUMutex);
        nodeLRUList.push_back(this);
    }
    nodeCount++;
}

node::~node()
{
    cout << "node destructor inode " << inodenumber() << endl;
}

void intrusive_ptr_add_ref(node *n)
{
    int a = n->refCnt++;
    if (a == 1) {
        cout << n->inodenumber() << " intrusive_ptr_add_ref " << a << endl;
    }
}

void intrusive_ptr_release(node *n)
{

    if (0 == --n->refCnt) {
        cout << n->inodenumber() << " intrusive_ptr_release " << n->refCnt << endl;
        //delete n;
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
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * threadNo));
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
            cout << "need to add a node " << i << " to hash" << endl;
            boost::intrusive_ptr <node> A =  new node(i);
        }
        if (++i > MAXNODES)
            i = 1;
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

void lruThread()
{
    while (!shutdown) {
        if (nodeCount <= THRESHOLD) {
            boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
            continue;
        }

        boost::mutex::scoped_lock lock(nodeLRUMutex);
        node *node = nodeLRUList.front();

        
    }
}

int main ()
{
    int i;
    boost::scoped_ptr<boost::thread>        mThreads[MAXNODES];
    for (i = 0; i < MAXNODES; i++) {
        mThreads[i].reset(new boost::thread(boost::bind(&random_io_thread,
                                                     i + 1)));
    }

    boost::scoped_ptr<boost::thread>        mThreadp;
    mThreadp.reset(new boost::thread(boost::bind(&prepareNodes)));

    boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
    shutdown = true;
    for (i = 0; i < MAXNODES; i++) {
        mThreads[i]->join();
        mThreads[i].reset();
    }
    cleanupHash();

    return 0;
}
