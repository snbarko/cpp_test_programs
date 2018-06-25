#include <iostream>

void function (void **ptr)
{
    int *p = new(int);
    *p = 11;

    *ptr = (void *)p;
}

void function1(void *ptr)
{
    int *p = (int *)ptr;

    std::cout << "value " << *p << std::endl;
}


int main ()
{
    void *p = NULL;

    function (&p);

    function1(p);

    return 0;
}
