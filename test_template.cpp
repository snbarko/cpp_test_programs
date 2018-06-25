#include <iostream>
#include <stdio.h>

template <class myType>

myType GetMax(myType a, myType b) {
    return (a > b ? a : b);
}

int main ()
{
    // int x = 11 ,y = 10, k;
    double x = 11.2 ,y = 11.1, k;

    // k = GetMax <int>(x, y);
    k = GetMax <double>(x, y);

    // printf("Max is %d\n", k);
    printf("Max is %f\n", k);
    return 0;
}
