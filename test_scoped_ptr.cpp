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
        myptr.reset(new int);
    }

    void stop()
    {
        myptr.reset();
    }

private:
    boost::scoped_ptr<def> myptr;
};

int main()
{
    abc z;
    z.start();
    z.stop();
    return 0;
}
