#include <iostream>
#include <linux/types.h>
#include <boost/atomic.hpp>
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

#define MAXTHREADS 200
boost::atomic<uint32_t> myvariable;
#define TIMES 10000

void random_io_thread_add(int threadNo)
{
    for(int i = 0; i < TIMES; i++)
    {
        myvariable.fetch_add( 1, boost::memory_order_relaxed );
        // myvariable++;
        // boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * threadNo));
    }

    // for(int i = 0; i < TIMES; i++)
    // {
    //     // myvariable.fetch_sub( 1, boost::memory_order_seq_cst );
    //     myvariable.fetch_sub( 1, boost::memory_order_relaxed );
    //     // boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * threadNo));
    // }


    // cout << "Exiting thread " << threadNo << endl;
}

void random_io_thread_sub(int threadNo)
{
    // for(int i = 0; i < TIMES; i++)
    // {
    //     myvariable.fetch_add( 1, boost::memory_order_relaxed );
    //     // myvariable++;
    //     // boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * threadNo));
    // }

    for(int i = 0; i < TIMES; i++)
    {
        // myvariable.fetch_sub( 1, boost::memory_order_seq_cst );
        myvariable.fetch_sub( 1, boost::memory_order_relaxed );
        // boost::this_thread::sleep(boost::posix_time::milliseconds(1000 * threadNo));
    }


    // cout << "Exiting thread " << threadNo << endl;
}


int main ()
{
    int i;
    boost::scoped_ptr<boost::thread>        mThreads[MAXTHREADS*2];

    while (1)
    {
    uint32_t value = myvariable;
    // std::cout << "At start value is " << value << std::endl;

    for (i = 0; i < MAXTHREADS; i++) {
        mThreads[i].reset(new boost::thread(boost::bind(&random_io_thread_add,
                                                     i + 1)));
    }

    
    for (i = MAXTHREADS; i < MAXTHREADS*2; i++) {
        mThreads[i].reset(new boost::thread(boost::bind(&random_io_thread_sub,
                                                     i + 1)));
    }

    // boost::this_thread::sleep(boost::posix_time::milliseconds(2000));

    for (i = 0; i < MAXTHREADS*2; i++) {
        mThreads[i]->join();
        mThreads[i].reset();
    }

    value = myvariable;

    if (value)
    {
        std::cout << "At end value is " << value << std::endl;
        break;
    }
    }

    return 0;
}
