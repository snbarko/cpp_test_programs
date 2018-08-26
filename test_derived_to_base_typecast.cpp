#include <iostream>

class A {
public:
    A()
    {
        dataA = 11;
    }
    ~A()
    {
    }
    void display()
    {
        std::cout << "This is " << dataA << std::endl;
    }
private:
    int dataA;
};

class B : public A
{
public:
    B():A()
    {
        dataB = 22;
        dataB2 = 33;
    }
    ~B()
    {
    }
    void display()
    {
        std::cout << "This is " << dataB << std::endl;
    }

private:
    int dataB;
    int dataB2;
};

int main ()
{
    B b;
    // A *a = dynamic_cast<A*> &b;
    A *a = (A *)&b;
    a->display();
    return 0;
}
