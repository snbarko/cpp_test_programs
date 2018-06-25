#include <iostream>

struct abc
{
    abc() // Whoa !! Struct can also have constructor !!
    {
        std::cout << "This is struct constructor" << std::endl;
    }
    int a; // By default members are public

    void member_f_struct() // OMG !! Member function inside a struct !!
    {
        std::cout << "This is member function of struct" << std::endl;
    }
};

class def
{
public:
    def()
    {
        std::cout << "This is class constructor" << std::endl;
    }
    int b; // By default members are private
    struct abc c;
    union abc_new {
        abc_new()
        {
            std::cout << "This is a union constructor inside class" << std::endl;
            union_member_f();
            
        }
        int show_internal_value()
        {
            return e;
        }
    private:
        int e;
        void union_member_f()
        {
            e = 99;
        }
    } d;
};

int main()
{
    struct abc a;
    a.a = 55;
    std::cout << "a.a is " << a.a << std::endl;
    a.member_f_struct(); // I am calling member function of a struct

    std::cout << ">>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<>>>>>>>>>>><<<<<<<<<<<<<<<<<<" << std::endl;
    def b;
    b.b = 66;
    std::cout << "b.b is " << b.b << std::endl;
    b.c.member_f_struct();
    std::cout << "b.d is " << b.d.show_internal_value() << std::endl;
    return 0;
}
