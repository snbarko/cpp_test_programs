#include <iostream>
#include <boost/noncopyable.hpp>

class myclass :
    private boost::noncopyable
{
public:
    myclass()
    {
        std::cout << "Default constructor\n";
    }
    ~myclass()
    {
        std::cout << "Destructor\n";
    }
};

int main ()
{
    myclass a;

    // Both lines below are invalid as noncopyable is mentioned
    // myclass b = a; 
    // b = a;

    return 0;
}
