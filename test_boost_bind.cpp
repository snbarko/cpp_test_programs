#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

int f(int a, int b)
{
    cout << "This is function f" << endl;
    return a + b;
}

void some_function(int some_value1, int some_value2, char some_char, boost::function<int (int)> functor)
{
    cout << "This is inside some function" << endl;
    // int result = functor(some_value1, some_value2);
    int result = functor(some_value1);
    cout << "Result is " << result << endl;
}

int main()
{
    // cout << "Sum of 11 and 22 is " << f(11,22) << endl;
    // int out = boost::bind(f, 11, 22)();
    // cout << "Using bind, sum of 11 and 22 is " << out << endl;
    // cout << "Direct using bind, sum of 11 and 22 is " <<  boost::bind(f, 11, 22)() << endl;
    // cout << "Using bind with _1, sum of 44 and 22 is " <<  boost::bind(f, _1, 22)(44) << endl;

    some_function(23, 33, 'a', boost::bind(f, _1, 55));
    return 0;
}
