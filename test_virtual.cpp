#include <iostream>
using namespace std;

class parent_A
{
public:
    void print_function();
};

class child_B : public parent_A
{
public:
    void print_function()
    {
        cout << "This is derived class print function." << endl;
    }
};

class child_C : public child_B
{
public:
    void print_function()
    {
        cout << "This is C derived" << endl;
    }
};

class child_D : public child_B
{
public:
    void test()
    {
        child_C u;
        child_B *a = &u;
        a->print_function();
    }
};

class Z
{
public:
    int a;
};

class Y
{
public:
    Y(Z i)
    {
        cout << "Copy constructor called" << endl;
        this->b = i.a;
    }
    char u;
    int b;
};

int main()
{
    Z *a = new(Z);
    a->a = 11;
    // Y *b = (Y*)a;
    Y b(*a);
    cout << "Value: " << b.b << endl;
    return 0;
};


void parent_A::print_function()
{
    cout << "This is base class print function." << endl;
}

// int main()
// {
//     // child_D n;
//     // n.test();

//     child_B z;
//     z.print_function();

//     parent_A *y = &z;
//     y->print_function();

//     // parent_A A;
//     // A.print_function();

//     // child_B B;
//     // B.print_function();

//     // parent_A C = A;
//     // C.print_function();
//     return 0;
// }
