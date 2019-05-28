#include <iostream>
#include <boost/scoped_array.hpp>

using namespace std;

template <class T>
class MyObject
{
public:
    void* operator new[](size_t siz, bool flag)
    {
        std::cout << "New operator array flag overloaded" << std::endl;
        return malloc(siz);
    }
    void* operator new[](size_t siz)
    {
        std::cout << "New operator array overloaded 2 size " << siz << std::endl;
        return malloc(siz);
    }
    void* operator new(size_t siz, bool flag)
    {
        std::cout << "New operator flag overloaded 3" << std::endl;
        return malloc(sizeof(MyObject<T>));
    }
    void* operator new(size_t siz)
    {
        std::cout << "New operator overloaded 4" << std::endl;
        return malloc(sizeof(MyObject<T>));
    }

    MyObject(T idx):MyIdx(idx)
    {
        cout << "This is object number " << idx << endl;
    }
    MyObject()
    {
        cout << "This is object" << endl;
    }
    
    ~MyObject()
    {
        cout << "This is destructor" << endl;
    }
    T MyIdx;
};

int main ()
{
    MyObject<int> intObj(55);
    MyObject<int>* intObjP = new MyObject<int>(66);
    MyObject<int>* intObjP2 = new (true) MyObject<int>(77);
    MyObject<int>* intObjP3 = new MyObject<int>[10];
    MyObject<int>* intObjP4 = new (true) MyObject<int>[10];
    boost::scoped_array<MyObject<int> > intObjP5(new (true) MyObject<int>[10]);
    boost::array
    
    return 0;
}
