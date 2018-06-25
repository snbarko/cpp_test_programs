#include <iostream>

class abc
{
private:
    static int a;
    static const int z = 77;
    static int y;
public:
    abc()
    {
        std::cout << "This is constructor of the class" << std::endl;
        b = 11;
        // abc::y = 55;
    }
    int b;
    void print_value()
    {
        std::cout << "Values a: " << a << " b: " << b << " " << z << " " << abc::y << std::endl;
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
