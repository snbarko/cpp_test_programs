#include <iostream>

class A
{
public:
    A() {}
    static void function() { std::cout << "Snehasish" << std::endl;}
};

class Z
{
public:
    Z() {}
    static void function() { std::cout << "Banerjee" << std::endl;}
};

class B
{
public:
    B() {}
    template<class T>
    void function1() { T::function();}
};

class C
{
public:
    C() {}
    template<class T>
    void function2() { b.function1<T>(); }
    B b;
};

int main()
{
    C c;
    c.function2<A>();
    c.function2<Z>();
    return 0;
}
