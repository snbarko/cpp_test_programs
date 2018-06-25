// This code will not compile as using explicit keyword it will prevent the
// object creation with char to pick the constructor with integer as argument.
#include <iostream>

class abc
{
public:
    abc()
    {
        std::cout << "Default constructor called" << std::endl;
    }
    // Below explicit keyword will prevent the object creation with below cons
    // when object is initialized with char
    abc(const char *a)
    {
        std::cout << "Constructor with a char * called " << a << " done." << std::endl;
    }
    explicit
    abc(int a)
    {
        std::cout << "Constructor with int called " << a << " done." << std::endl;
    }

    // Below is the ultimate fix for the problem we mentioned
    // abc (char a)
    // {
    //     std::cout << "Constructor with a char called " << a << " done." << std::endl;
    // }
};

int main()
{
    std::cout << "Hello World!" << std::endl;

    // abc A;
    // abc B("b");
    abc C = 'A'; // 'A' is converted to integer while calling constructor with integer input
    
    return 0;
}
