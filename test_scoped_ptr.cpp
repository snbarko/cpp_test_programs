#include <iostream>
#include <boost/scoped_ptr.hpp>

class def
{
    public:
    def()
    {
        std::cout << "def constructor" << std::endl;
    }

    ~def()
    {
        std::cout << "def destructor" << std::endl;
    }
};

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

    void start()
    {
        myptr.reset(new int(11));
        std::cout << "scoped ptr addr " << &myptr << " raw " << myptr.get() << " value " << *( myptr.get()) << std::endl;
    }

    void stop()
    {
        myptr.reset();
    }

private:
    // boost::scoped_ptr<def> myptr;
    boost::scoped_ptr<int> myptr;
};

int main()
{
    abc z;
    z.start();
    z.stop();
    return 0;
}
