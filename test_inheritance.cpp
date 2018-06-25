#include <iostream>

class A
{
public:
    A()
    {
        std::cout<< "A constructor" << std::endl;
    }
    void function(int a, int b = 11);
};

void A::function(int a, int b = 11)
{
    std::cout << "a is " << a << " b is " << b << std::endl;
}

int main()
{
    A z;

    z.function(22);
    return 0;
}
