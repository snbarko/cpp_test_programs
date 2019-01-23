#include <iostream>

class A
{
public:
    static void mystaticfunction(A a)
    {
        a.display();
    }
    void display()
    {
        std::cout << "value is " << data < std::endl;
    }
    A()
    {
        data = 55;
        setCallback(mystaticfunction);
    }
private:
    int data;
};

class B
{
public:
    B(void *ad)
    {
        std::cout << "this is B";
        adata = ad;
    }
    void setCallback(void (*function)(void *))
    {
        mCallback = function;
    }
    void ultimatefunc()
    {
        mCallback();
    }
private:
    void(*)(void *) mCallback;
    void *adata;
};

int main ()
{
    A y;
    B z((void *)&y);
    return 0;
}
