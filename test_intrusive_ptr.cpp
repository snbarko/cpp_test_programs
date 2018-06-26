#include <iostream>
#include <boost/intrusive_ptr.hpp>

namespace snb {
class A
{
public:
    A(int dataMine):data(dataMine), refCount(0) {
        std::cout << "THis is class constructor" << std::endl;
    }

    ~A() {
        std::cout << "THis is class destructor" << std::endl;
    }

    void display ()
    {
        std::cout << "Data value is " << data << " ref count " << refCount << std::endl;
    }
private:
    int data;
public:
    int refCount;
};

    void intrusive_ptr_add_ref(A* a)
    {
        std::cout << "This is intrusive_ptr_add_ref of A" << std::endl;
        a->refCount++;
    }
    void intrusive_ptr_release(A* a)
    {
        std::cout << "This is intrusive_ptr_release of A" << std::endl;
        if (--a->refCount == 0)
            delete a;
    }

}
int main()
{
    boost::intrusive_ptr<snb::A> a(new snb::A(11));

    a->display();
    // boost::intrusive_ptr<snb::A> b(a);
    // a->display();
    // b->display();
    
    return 0;
}
