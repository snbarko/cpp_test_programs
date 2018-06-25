#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class A
{
public:
    A()
    {
        cout << "This is A constructor" << endl;
        data = 11;
    }
    ~A()
    {
        cout << "This is A destructor" << endl;
    }

    void operator delete(void *p)
    {
        cout << "This is delete operator overloaded" << endl;
        free(p);
    }

    void* operator new(size_t size)
    {
        cout << "new operator overloaded size " << size << endl;
        return malloc(size);
    }

    void function()
    {
        cout << "data is " << data << endl;
    }
private:
    int data;
};

int main ()
{
    A *a = new(A);
    a->function();
    delete a;
    return 0;
}
