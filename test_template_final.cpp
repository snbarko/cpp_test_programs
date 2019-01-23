#include <iostream>
using namespace std;

template <class T>
class Stack
{
public:
    Stack(int size):mTop(-1), mSize(size)
    {
        mHead = new T[size];
    }
    ~Stack()
    {
        delete mHead;
    }
    void push(T value)
    {
        if (mTop == (mSize - 1))
        {
            cout << "Stack full" << endl;
            return;
        }
        mHead[++mTop] = value;
    }
    
    T pop()
    {
        if (mTop == -1)
        {
            throw "Stack is empty";
            // throw exception("STack is empty");
        }
        return mHead[mTop--];
    }
    
private:
    int mTop;
    int mSize;
    T *mHead;
};

int main()
{
    try
    {
        Stack<int> s1(2);
        s1.push(11);
        cout << s1.pop() << endl;
        s1.push(12);
        s1.push(13);
        s1.push(14);
        cout << s1.pop() << endl;
        cout << s1.pop() << endl;
        cout << s1.pop() << endl;
        cout << s1.pop() << endl;
        s1.push(12);
        s1.push(13);
        s1.push(14);
        cout << s1.pop() << endl;
        cout << s1.pop() << endl;

        Stack<char> s2(2);
        s2.push('k');
        cout << s2.pop() << endl;
        s2.push('t');
        s2.push('r');
        s2.push('a');
        cout << s2.pop() << endl;
        cout << s2.pop() << endl;
        cout << s2.pop() << endl;
        cout << s2.pop() << endl;
        s2.push('a');
        s2.push('d');
        s2.push('c');
        cout << s2.pop() << endl;
        cout << s2.pop() << endl;
    }
    catch (exception& e)
    {
        cout << "Exception caught. Exiting cleanly." << e.what() << endl;
    }
    catch (...)
    {
        cout << "Exception caught. Exiting cleanly." << endl;
    }

    return 0;
}
