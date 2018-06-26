#include <iostream>
using namespace std;

class B {
public:
    B()
    {
        cout << "This is B constructor" << endl;
    }
    ~B()
    {
        cout << "This is B destructor" << endl;
    }
};

class C {
public:
    C()
    {
        cout << "This is C constructor" << endl;
    }
    ~C()
    {
        cout << "This is C destructor" << endl;
    }
};


class A {
public:
    A()
    {
        cout << "This is A constructor" << endl;
    }
    virtual ~A()
    {
        cout << "This is A destructor" << endl;
        {
            cout << "Executing other statements here as well" << endl;
        }
    }
private:
    B b;
    C c;
};

int main ()
{
    A a;
    return 0;
}
