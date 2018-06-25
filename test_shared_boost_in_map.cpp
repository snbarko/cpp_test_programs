#include <iostream>
#include <map>
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

typedef std::map<int, boost::shared_ptr<A> > MAP;

MAP mymap;

void function(boost::shared_ptr<A> b)
{
    cout << "This is function " << b.use_count() << " is the ref count" << endl;
}

int main ()
{
    boost::shared_ptr<A> a(new A);

    cout << "a ref count " << a.use_count() << endl;

    mymap.insert(make_pair(1, a));
    mymap.insert(make_pair(2, a));
    
    
    cout << "post a ref count " << a.use_count() << endl;

    MAP::iterator It = mymap.find(1);
    if (It != mymap.end()) {
        cout << "found entry" << endl;
        mymap.erase(It);
    }

    It = mymap.begin();
    while (It != mymap.end()) {
        cout << "Element " << *It->first() << endl;
        It++;
    }

    cout << "post a ref count " << a.use_count() << endl;

    return 0;
}
