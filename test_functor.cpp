#include <iostream>
#include <stdio.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>

class add_x {
public:
    add_x(int x) : x(x) {}
    int operator()(int y) const { return x + y;}
    void method(std::string param)
    {
        std::cout << "Number is " << x << " and i am " << param << std::endl;
    }
    void method(std::string param, int a)
    {
        std::cout << "Number is " << x << " and i am " << param << " number " << a << std::endl;
    }
private:
    int x;
};

int main()
{
    add_x add45(45);
    int x = add45(1);
    printf("After add value is %d\n", x);
    // boost::function<void (std::string)> callback;
    // callback = boost::bind(&add_x::method, add45, _1);
    // callback("Snehasish");
    boost::bind(&add_x::method, add45, _1)("snehasish");
    boost::bind(&add_x::method, add45, _2)("snehasish", 34);
    return 0;
}
