#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/utility.hpp>


namespace ptime = boost::posix_time;

class abc
{
public:
    abc()
    {
        std::cout << "Contructor" << std::endl;
    }
    ~abc()
    {
        std::cout << "Destructor" << std::endl;
    }

    void threadfunction()
    {
        while (!stopThread) {
            std::cout << "SNB this is function in thread" << std::endl;
            boost::this_thread::sleep(ptime::milliseconds(3000));
        }

        std::cout << "Thread is exiting" << std::endl;
    }

    void start()
    {
        mythread.reset(new boost::thread(boost::bind(&abc::threadfunction, this)));
    }

    void stop()
    {
        stopThread = true;
        std::cout << "Waiting for thread to join" << std::endl;
        mythread->join();
        std::cout << "SNB thread joined" << std::endl;
        mythread.reset();
    }

private:
    boost::scoped_ptr<boost::thread> mythread;
    bool stopThread;
};

int main()
{
    abc z;
    z.start();
    z.stop();
    return 0;
}
