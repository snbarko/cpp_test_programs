#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "A constructor" << std::endl;
    }

    class B
    {
    public:
        B()
        {
            std::cout << "B constructor" << std::endl;
        }
    };
private:
    B b;
};

int main()
{
    // A a;

    typename A::B ;

    B b;
    
    return 0;
}
