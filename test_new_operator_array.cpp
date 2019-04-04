#include <iostream>
#include <stdlib.h>

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
        std::cout << "New operator overloaded 2 size " << siz << std::endl;
        // return ::new A();
        return malloc(sizeof(A));
    }

    void* operator new[](size_t siz)
    {
        std::cout << "New operator overloaded 3 size " << siz << std::endl;
        // return ::new A();
        return malloc(sizeof(A));
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

int main()
{
    bool flag = false;
    A *a = new (flag) A();
    std::cout << "Barrier" << std::endl;
    A *b = new A();
    std::cout << "Barrier" << std::endl;

    A *c = new A[10];
    // A c(33);
    // A* d = &c;
    // c.print();
    // d->print();
    // A* e = new (d) A(55);
    // e->print();
    return 0;
}
