#include <iostream>

int function()
{
    throw "THrowing";
    return 11;
}

int function1() throw()
{
    int a = 1;
    try {
        a =  function();
    } catch(const std::exception &e) {
        std::cout << "snb" << e.what() << std::endl;
    }
    return a;
}

int main()
{
    int a = function();
    std::cout << a << std::endl;
    return 0;
}
