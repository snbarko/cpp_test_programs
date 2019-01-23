#include <iostream>

class B;

class A
{
public:
    A(const B* b):mb(b)
    {
        std::cout << "A cons" << std::endl;
    }
    void function();
private:
    const B* mb;
};

class B
{
public:
    B()
    {
        std::cout << "B cons" << std::endl;
        A a(this);
    }
    void function()
    {
        std::cout << "This is B function" << std::endl;
    }
};

void A::function()
{
    std::cout << "This is A function" << std::endl;
    mb->function();
}

int main ()
{
    B b;
    return 0;
}
