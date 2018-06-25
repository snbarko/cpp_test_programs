#include <iostream>
#include <map>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;

class A
{
public:
    A(int dt)
    {
        cout << "A constructor" << endl;
        data = dt;
    }
    ~A()
    {
        cout << "A destructor" << endl;
    }
    int data;
};

class B
{
public:
    B(int dt2)
    {
        cout << "B constructor" << endl;
        data2 = dt2;
    }
    ~B()
    {
        cout << "B destructor" << endl;
    }
    int data2;
};

class D
{
public:
    D(boost::shared_ptr<A> ax, boost::shared_ptr<B> by)
    {
        cout << "D constructor" << endl;
        data3 = ax->data;
        data4 = by->data2;
    }
    ~D()
    {
        cout << "D destructor" << endl;
    }
    int data3;
    int data4;
};

class C
{
public:
    C():a(new A(11)), b(new B(22)), d(a, b)
    {
        cout << "C constructor" << endl;
    }
    ~C()
    {
        cout << "C destructor" << endl;
        a.reset();
        b.reset();
    }
    boost::shared_ptr<A> a;
    boost::shared_ptr<B> b;
    D d;
};


int main ()
{
    // boost::shared_ptr<A> a(new A);

    C c;

    return 0;
}
