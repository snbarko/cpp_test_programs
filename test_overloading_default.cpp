#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "This is A constructor" << endl;
    }
    ~A()
    {
        cout << "This is A destructor" << endl;
    }

    virtual void function(int data1, int data2 = 66);
};

void A::function(int data1, int data2)
{
    cout << "This is function of A " << data1 << " " << data2 << endl;
}

class B : public A
{
public:
    B()
    {
        cout << "This is B constructor" << endl;
    }
    ~B()
    {
        cout << "This is B destructor" << endl;
    }

    void function(int data1, int data2 = 55);
};

void B::function(int data1 int data2)
{
    cout << "This is function of B " << data1 << " " << data1 << endl;
}

int main ()
{
    A *b = new B;

    b->function(33);
    return 0;
}
