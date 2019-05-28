#include <iostream>
#include <boost/scoped_array.hpp>

using namespace std;

class MyObject
{
public:
    void* operator new[](size_t siz, bool flag)
    {
        std::cout << "New operator overloaded" << std::endl;
        // return ::new A();
        return malloc(sizeof(MyObject));
    }
    void* operator new[](size_t siz)
    {
        std::cout << "New operator overloaded 2" << std::endl;
        // return ::new A();
        return malloc(sizeof(MyObject));
    }
    void* operator new(size_t siz, bool flag)
    {
        std::cout << "New operator overloaded 3" << std::endl;
        // return ::new A();
        return malloc(sizeof(MyObject));
    }
    void* operator new(size_t siz)
    {
        std::cout << "New operator overloaded 4" << std::endl;
        // return ::new A();
        return malloc(sizeof(MyObject));
    }

    MyObject(int idx):MyIdx(idx)
    {
        cout << "This is object number" << idx << endl;
    }
// private:
    MyObject()
    {
        cout << "This is object" << endl;

    }
    
    ~MyObject()
    {
        cout << "This is object destructor" << endl;
    }
    int MyIdx;
};

class MyObjStore
{
public:
    MyObjStore():mObjects(new (true) MyObject[10])
    {
        
        cout << "This is my object store" << endl;
    }
private:
    boost::scoped_array<MyObject> mObjects;
};

int main ()
{
    MyObjStore str;
    return 0;
}
