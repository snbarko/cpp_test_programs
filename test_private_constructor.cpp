// Singleton class implementation using private constructor

#include <iostream>

using namespace std;

class A {
private:
    A()
    {
        cout << "default constructor" << endl;
        data = 55;
    }
    int data;
    static A *me;
public:
    static A* get_object()
    {
        if (me) {
            cout << "Object cannot be created" << endl;
            return NULL;
        } else {
            // valid = 1;
            me = new A();
            return me;
        }
    }
    void print_value()
    {
        cout << "Data is " << data << endl;
    }
    ~A()
    {
        cout << "default destructor" << endl;
        A::me = NULL;
    }
    // static int valid;
};

A* A::me = NULL;

int main ()
{
    A* a = A::get_object();
    if (a)
        a->print_value();
    A *b = A::get_object();
    delete a;
    A *c = A::get_object();
    delete c;
    return 0;
}
