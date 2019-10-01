#include <iostream>

constexpr bool func(int a)
{
    if (a % 2)
        return false;
    else
        return true;
}

class abc
{
private:
    static int a;
    static const int z = 77;
    static int y;
    // static int x = 55; // Not allowerd inline initialization without const
public:
    static const int x = func(12) ? 12 : 13;

    abc()
    {
        std::cout << "This is constructor of the class" << std::endl;
        b = 11;
        // abc::y = 55;
    }
    int b;
    void print_value()
    {
        std::cout << "Values a: " << a << " b: " << b << " z " << z << " y " << abc::y << " x " << x << std::endl;
    }
    static void print_static_value()
    {
        std::cout << "Value of a " << abc::a << std::endl;
    }
};

void function1()
{
    // abc::y = 55;
}

int abc::a;
int abc::y = 55;
// int abc::x;

int main ()
{
    abc a;
    // abc::a = 99;
    // abc::y = 11;
    function1();
    a.print_value();
    abc::print_static_value();
    return 0;
}
