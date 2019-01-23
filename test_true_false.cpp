#include <iostream>

int main()
{
    if (!(false || true)) {
        std::cout << "print me" << std::endl;
    }
    return 0;
}
