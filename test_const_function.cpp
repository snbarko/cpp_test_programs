#include <iostream>

class A
{
public:
    A(int _data) : data(_data) {}
    A():data(0) {}
    int& getData() const { return data; }
private:
    int data;
};

int main()
{
    const A a(55);
    std::cout << a.getData() << std::endl;

    return 0;
}
