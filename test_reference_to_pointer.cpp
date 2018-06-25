#include <iostream>

class A
{
    A()
    {
        std::cout << "A constructor" << std::endl;
    }
    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }

};

void function(void *&ptr)
{
    int*ptr1 = (int *)ptr;
    
    ptr1 = new(int);
    
    *ptr1 = 11;
}

int main ()
{
    void *ptr = NULL;

    function (ptr);

    int *ptr2 = (int *)ptr;

    std::cout << "value is " << *ptr2 << std::endl;
    
    return 0;
}
