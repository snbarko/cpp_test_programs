#include <iostream>
#include <stdlib.h>
#include <boost/scoped_ptr.hpp>

class A
{
public:
    void* operator new(size_t siz, bool flag)
    {
        std::cout << "New operator overloaded" << std::endl;
        // return ::new A();
        return malloc(sizeof(A));
    }
    void* operator new(size_t siz)
    {
        std::cout << "New operator overloaded 2" << std::endl;
        // return ::new A();
        return malloc(sizeof(A));
    }

    void operator delete(void *ptr)
    {
        std::cout << "delete operator overloaded" << std::endl;
        free(ptr);
    }

    A()
    {
        std::cout << "Constructor A" << std::endl;
    }
    A(int data) : mydata(data)
    {
        std::cout << "Constructor A" << std::endl;
    }
    void print()
    {
        std::cout << "Data is " << mydata << " add " << this << std::endl;
    }
private:
    int mydata;

};

class B : public A
{
public:
    B() { std::cout << "Constructor in B" << std::endl;}
    // void* operator new(size_t siz)
    // {
    //     std::cout << "New operator in B" << std::endl;
    //     // return ::new A();
    //     return malloc(sizeof(B));
    // }

    // void operator delete(void *ptr)
    // {
    //     std::cout << "delete operator in B " << ptr << std::endl;
    //     free(ptr);
    // }
    
};

int main()
{
//     bool flag = false;
//     A *a = new (flag) A();
//     std::cout << "Barrier" << std::endl;
//     A *b = ::new A();
//     A *c = new A();
//     delete a;
//     delete b;
//     delete c;

    // B *a = new B();
    // delete a;

    boost::scoped_ptr<B> b;
    b.reset(new B());
    std::cout << "Barrier" << std::endl;
    // A c(33);
    // A* d = &c;
    // c.print();
    // d->print();
    // A* e = new (d) A(55);
    // e->print();
    return 0;
}
