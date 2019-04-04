#include <iostream>
#include <string.h>

void function(const char* ptr)
{
    std::cout << ptr << std::endl;
    // strcpy(ptr, "Banerjee"); // Not allowed
    ptr = ptr + 1; // Allowed
    std::cout << ptr << std::endl;
}

void function2(char * const ptr)
{
    std::cout << ptr << std::endl;
    strcpy(ptr, "Banerjee"); // Allowed
    // ptr = ptr + 1; // Not allowed
    std::cout << ptr << std::endl;
}

int main()
{
    char buffer[1024];

    strcpy(buffer, "Snehasish");
    function(buffer);
    function2(buffer);

    return 0;
}
