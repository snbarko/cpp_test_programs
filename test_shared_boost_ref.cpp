#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A constructor" << endl;
    }
    ~A()
    {
        cout << "A destructor" << endl;
    }
};

void function(boost::shared_ptr<A> b)
{
    cout << "This is function " << b.use_count() << " is the ref count" << endl;
}

int main ()
{
    boost::shared_ptr<A> a(new A);

    cout << "a ref count " << a.use_count() << endl;
    function(a);
    cout << "post a ref count " << a.use_count() << endl;

    a.reset();
    if (a) {
        cout << "shared ptr is valid" << endl;
    } else {
        cout << "shared ptr is not valid" << endl;
    }

    return 0;
}
