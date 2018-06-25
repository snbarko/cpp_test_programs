#include <iostream>

class abc {
public:
    void print(int a) {
        std::cout << a << std::endl;
    }

    void print(char a) {
        std::cout << a << std::endl;
    }

};

int main ()
{
    abc a;
    a.print(11);
    return 0;
}
