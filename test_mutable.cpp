#include <iostream>
using namespace std;

class abc {
private:
    mutable int a;
    int b;
public:
    abc (int y = 11, int z = 22): a(y), b(z) {
    }
    void function() const {
        cout << "a is " << a << endl;
        cout << "b is " << b << endl;
    }

    void modify(int t, int s) {
        a = t;
        b = s;
    }

    void modify_a(int t) const {
        a = t;
    }
};

int main()
{
    abc d;
    d.function();
    d.modify(33,44);
    d.function();
    d.modify_a(99);
    d.function();
    return 0;
}
