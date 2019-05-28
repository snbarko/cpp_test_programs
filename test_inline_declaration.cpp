#include <iostream>

class abc
{
public:
    inline void function();
    int data;
};

inline void abc::function()
{
    data = 55;
}

int main()
{
    abc a;
    a.function();
    return 0;
}
