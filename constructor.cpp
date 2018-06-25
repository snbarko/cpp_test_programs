#include <iostream>

class abc {
public:
    abc():
        a(55),
        b(44)

    {
        std::cout << "Constructor called" << std::endl;
        if (1)
        {
            do {
                
            } while (0);
        }
        else
        {
            
        }
    }
private:
    int a;
    int b;
    char c;
};

int main ()
{
    abc z;
    return 0;
}
