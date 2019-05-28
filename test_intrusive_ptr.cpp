#include <iostream>
#include <boost/intrusive_ptr.hpp>
#include <vector>
#include <boost/container/static_vector.hpp>

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
    char charme[1024];
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

void function(boost::intrusive_ptr<snb::A> c)
{
    c->display();
    boost::intrusive_ptr<snb::A> d;
    d = c;
    c->display();
    c->display();
    boost::intrusive_ptr<snb::A> e;
    e = d;
    c->display();
    d->display();
    e->display();
}

class B
{
public:
    B()
    {
    }
private:
    boost::intrusive_ptr<snb::A> data;
};

boost::container::static_vector<boost::intrusive_ptr<snb::A>, 10 > dVector;
int main()
{
    boost::intrusive_ptr<snb::A> a(new snb::A(11));

    a->display();
    boost::intrusive_ptr<snb::A> b(a);
    a->display();
    b->display();

    function(b);

    std::cout << sizeof(B) << std::endl;
    b->display();
    std::cout << sizeof(B) << std::endl;
    dVector.emplace_back(a);
    // dVector[0] = a;
    std::cout << sizeof(B) << std::endl;
    b->display();
    dVector[0].get()->display();
    return 0;
}
