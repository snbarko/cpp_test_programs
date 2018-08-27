#include <iostream>
#include <stdio.h>

struct something { int data;char roll; } __attribute__((aligned(64))); //  Set an alignment

int main ()
{
    struct something a;

    std::cout << "Size of struct is " << sizeof(struct something) << std::endl;
    return 0;
}
