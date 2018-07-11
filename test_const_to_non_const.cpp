#include <iostream>

void function (const int &b)
{
    int& c = *(const_cast<int*> (&b));

    std::cout << "c " << c << std::endl;
    c++;
}

int main ()
{
    const int a = 55;
    function (a);
    std::cout << "a " << a << std::endl;
    return 0;
}
