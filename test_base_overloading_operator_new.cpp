#include <iostream>
#include <stdlib.h>

class Base
{
public:
    Base()
    {
        if (data == 1)
            data = 2;
        else
            data = 1;

        std::cout << "Base class constructor this: " << this << " data " << data << std::endl;
    }
    static void* operator new(size_t size)
    {
        std::cout << "Base class operator new overloaded size  " << size << std::endl;
        // return ::new Base();
        return malloc(size);
    }
private:
    int data;
};

class Derived : public Base
{
public:
    Derived():Base()
    {
        data2 = 55;
        std::cout << "Derived class constructor this " << this <<  " data2 " << data2 << std::endl;
    }
    void* operator new(size_t size)
    {
        std::cout << "Derived class operator new overloaded size " << size << std::endl;
        return malloc(size);
        // return ::new Derived();
    }
private:
    int data2;

};

int main()
{
    // Base *b = new Base();

    Derived *d = new Derived();
    return 0;
}
