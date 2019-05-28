#include <iostream>

class A
{
public:
    A(int& _b): // b(_b),
                c(55)
    {
    }
    // int& b;
    int c;
};
int main ()
{
    int a = 5;
    A z(a);
    std::cout << sizeof (A)  << std::endl;
    return 0;
}
