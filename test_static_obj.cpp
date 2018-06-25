#include <iostream>

class abc
{
// private:
public:
    // friend class def;
    abc()
    {
        std::cout << "THis is abc constructor" << std::endl;
        b = 66;
    }
// private:
    static int a;
    int b;
};

class def
{
public:
    def():y()
    {
        std::cout << "THis is constructor" << y.b << abc::a << std::endl;
        
    }
    abc y;
};

int abc::a = 55;
int main ()
{
    def z;
    std::cout << abc::a << std::endl;
    return 0;
}

