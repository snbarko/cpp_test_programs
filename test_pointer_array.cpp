#include <iostream>

class abc
{
public:
    abc()//:arr()
    {
        if (arr[0] == NULL)
            std::cout << "null" << std::endl;
        else
            std::cout << "not null" << std::endl;
    }
    int *arr[4];
    int a;
};

int main()
{
    abc z;
    int *y[10] = {NULL};
    return 0;
}
