#include <iostream>
using namespace std;

class A {
public:
    A() {
        int c;
        b = 5;
        c = b;
    }

    void function()
    {
    }
    
    int b;
};

// typedef struct a
// {
// } A;

int main ()
{
    A a;
    cout << "size of a " << sizeof(a) << endl;
    return 0;
}
