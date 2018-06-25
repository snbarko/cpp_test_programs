#include <iostream>
#include <vector>
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

typedef std::vector<int > VECTOR;

VECTOR myvector;

void function(boost::shared_ptr<A> b)
{
    cout << "This is function " << b.use_count() << " is the ref count" << endl;
}

int main ()
{
    boost::shared_ptr<A> a(new A);

    cout << "a ref count " << a.use_count() << endl;

    myvector.push_back(1);
    myvector.push_back(2);
    myvector.push_back(3);
    myvector.push_back(3);
    myvector.push_back(5);
    
    cout << "post a ref count " << a.use_count() << endl;

    // MAP::iterator It = mymap.find(1);
    // if (It != mymap.end()) {
    //     cout << "found entry" << endl;
    //     mymap.erase(It);
    // }

    VECTOR::iterator vIt = find(myvector.begin(), myvector.end(), 3);

    if (vIt != myvector.end()) {
        cout << "Found vector element" << endl;
    } else {
        cout << "Not found vector element" << endl;
    }
    cout << "Size of vector " << myvector.size() << endl;
    myvector.erase(std::remove(myvector.begin(), myvector.end(), 3),  myvector.end());

    cout << "Size of vector " << myvector.size() << endl;
    vIt = find(myvector.begin(), myvector.end(), 3);

    if (vIt != myvector.end()) {
        cout << "Found vector element" << endl;
    } else {
        cout << "Not found vector element" << endl;
    }

    vIt = myvector.begin();
    while (vIt != myvector.end()) {
        cout << "Element : " << *vIt << endl;
        vIt++;
    }

    cout << endl << endl;

    myvector.erase(std::find(myvector.begin(), myvector.end(), 6));

    cout << "Size of vector " << myvector.size() << endl;
    vIt = find(myvector.begin(), myvector.end(), 2);

    if (vIt != myvector.end()) {
        cout << "Found vector element" << endl;
    } else {
        cout << "Not found vector element" << endl;
    }

    vIt = myvector.begin();
    while (vIt != myvector.end()) {
        cout << "Element : " << *vIt << endl;
        vIt++;
    }


    cout << "post a ref count " << a.use_count() << endl;

    return 0;
}
