#include <iostream>
#include <boost/scoped_array.hpp>

using namespace std;

class MyObject
{
public:
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
    MyObjStore():mObjects(new MyObject[10])
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
