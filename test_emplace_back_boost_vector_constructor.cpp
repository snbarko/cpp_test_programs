#include <iostream>
#include "boost/container/vector.hpp"
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
    typedef boost::container::vector<A*> BList;

    AList alist;
    BList blist;

    // alist.emplace_back(11, 22, 'c');
    // alist.emplace_back(55, 66, 'a');
    // alist.emplace_back(77, 'b', 88);
    // alist.emplace_back(404);
    int num1 = 11, num2 = 22;
    char charme = 'a';

    for (int i = 0; i < 4; i++)
    {
        A *a = new A(num1, num2, charme);
        alist.emplace_back(*a);
        blist.emplace_back(a);
        num1++;num2++;charme++;
    }

    AList::iterator it = alist.begin();

    for (;it!=alist.end();++it)
    {
        it->display();
    }

    for (auto& it1 : blist)
    {
        it1->display();
    }
    
    return 0;
}
