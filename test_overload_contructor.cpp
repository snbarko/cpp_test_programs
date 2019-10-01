#include <iostream>

class A
{
public:
    A(int a = 22):data(a)
    {
    }

    void display()
    {
        std::cout << "Value is " << data << std::endl;
    }
private:
    int data;
};

int main()
{
    A a(11);
    a.display();
    // A b;
    // b.display();
    return 0;
}
