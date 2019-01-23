#include <iostream>

class A {
public:
    int f();
    // int (A::*x)(); // <- declare by saying what class it is a pointer to
};

int A::f() {
    return 1;
}


int main() {
    A a;
    int (A::*x)();
    // a.x = &A::f; // use the :: syntax
    x = &A::f;

    // printf("%d\n",(a.*(a.x))()); // use together with an object of its class
}

// class abc
// {
// public:
//     void func() {}
//     void func(int data) {}
// };

// // // #define FUNC (a.*(&abc::func))
// // // #define FUNC (a.ptr1)
// using namespace std;
   
// void (abc::*fp)(int a); // pointer to int f(int)
// fp = abc::func; // points to myfunc(int)
   
// int main()
// {
//     // abc a;

//     return 0;
// }
   
// // int myfunc(int a)
// // {
// //     return a;
// // }
   
