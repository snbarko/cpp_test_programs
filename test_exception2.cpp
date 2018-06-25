#include <iostream>
using namespace std;

class abc {
public:
    abc() {
        cout << "this is constructor" << endl;
    }
    ~abc() {
           cout << "this is destructor" << endl;
    }
};

void function2() {
    cout << "this is function2" << endl;
    throw "Panic!!";
    return;
}

void function1() {
    abc a;
    cout << "this is function1" << endl; 
    function2();
    cout << "this is function1 exiting" << endl;
}

int main()
{
    function1();
    return 0;
}
