#include <iostream>
#include <boost/thread/mutex.hpp> // Header file for boost::mutex
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/is_locked_by_this_thread.hpp>
#include <boost/thread/lock_options.hpp>
#include <pthread.h>

class snbmutex : public boost::mutex
{
public:
    void lock()
    {
        std::cout << "SNB lock came thread " << boost::this_thread::get_id() << std::endl;
        if (!isLockedByCaller()) {
            boost::mutex::lock();
            m_holder = boost::this_thread::get_id();
            m_actual_holder = m_holder;
            std::cout << "SNB locking now " << m_holder << std::endl;
        } else {
            std::cout << "SNB already locked by this thread" << m_holder << std::endl;
        }
    }
    void unlock()
    {
        std::cout << "SNB unlock no flag" << m_holder << std::endl;
        m_holder = boost::thread::id();
        boost::mutex::unlock();
    }
 
    bool amIOwner()
    {
        bool returnme = actualHolder();
        if (returnme == true)
            m_actual_holder = boost::thread::id();
        return returnme;
    }
private:
    bool isLockedByCaller()
    {
        return m_holder == boost::this_thread::get_id();
    }
    bool actualHolder()
    {
        return m_actual_holder == boost::this_thread::get_id();
    }
    boost::thread::id m_holder;
    boost::thread::id m_actual_holder;
};

class snb_unique_lock : public boost::unique_lock<snbmutex>
{
public:
    snb_unique_lock(snbmutex &s):boost::unique_lock<snbmutex>(s, boost::defer_lock_t())
    {
        mtx = &s;
        mtx->lock();
        lock_owner = mtx->amIOwner();
        std::cout << "SNB did I lock the mutex?" << lock_owner << std::endl;
    }
    ~snb_unique_lock()
    {
        if (lock_owner) {
            std::cout << "calling unlock" << std::endl;
            mtx->unlock();
        } else {
            std::cout << "Not calling unlock" << std::endl;
        }
    }
    bool owns_lock() const BOOST_NOEXCEPT
    {
        return lock_owner;
    }

private:
    bool lock_owner;
    snbmutex *mtx;
};

class A
{
public:
    A():
        // mMutex(),
        mdata(11)
    {
        std::cout << "A constructor" << std::endl;
        pthread_mutex_init(&m,NULL);
    }
    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
    void outerAccessFunction(int mydata)
    {
        {
            snb_unique_lock lock(mMutex);
            std::cout << "This is  outerAccessFunction" << std::endl;
            internalAccessFunction();
            mdata = mydata;
            std::cout << "outerAccessFunction ending" << std::endl;
        }

        internalAccessFunction();
    }
private:
    void internalAccessFunction()
    {
        std::cout << "This is  internalAccessFunction" << std::endl;
        snb_unique_lock lock1(mMutex);

        // Do nothing
        std::cout << "This is  internalAccessFunction2 ending " << std::endl;
    }
    int mdata;
    pthread_mutex_t m;
    snbmutex mMutex;
};

volatile int shutdown = 0;

void thread_function()
{
    while (!shutdown)
    {
    }
}

int main ()
{
    A a;
    boost::thread t1(thread_function);
    a.outerAccessFunction(11);
    shutdown = 1;
    t1.join();
    return 0;
}
