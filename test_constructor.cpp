#include <iostream>

class B
{
public:
    B(int data)
    {
        std::cout << "this is B" << std::endl;
    }
    void function()
    {
    }
};

class A
{
    public:
    A():b(55)// ,b.function()
    {
        std::cout << "this is A" << std::endl;
        b.function();
        // b = new B(55);
    }
private:
    B b;
};

int main ()
{
    A a;
    return 0;
}
