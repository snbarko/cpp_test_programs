#include <iostream>
#include "boost/container/static_vector.hpp"

class A
{
public:
    A(int a, int b, char c)
    {
        std::cout << "This is A constructor 1." << std::endl;
        dataA = a;
        dataB = b;
        charC = c;
    }
    A(int b, char c, int a)
    {
        std::cout << "This is A constructor 2." << std::endl;
        dataA = a;
        dataB = b;
        charC = c;
    }
    A(int b)
    {
        std::cout << "This is A constructor 3." << std::endl;
        dataA = 202;
        dataB = b;
        charC = 'z';
    }

    void display()
    {
        std::cout << "A " << dataA << " B " << dataB << " C " << charC << std::endl;
    }
private:
    int dataA;
    int dataB;
    char charC;
};

typedef boost::container::static_vector<A, 5> AList;

int main ()
{
    AList alist;

    alist.emplace_back(11, 22, 'c');
    alist.emplace_back(55, 66, 'a');
    alist.emplace_back(77, 'b', 88);
    alist.emplace_back(404);

    AList::iterator it = alist.begin();

    for (;it!=alist.end();++it)
    {
        it->display();
    }
    
    return 0;
}
