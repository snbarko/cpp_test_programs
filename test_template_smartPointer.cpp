#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
public:
    MyString()
    {
        //cout << "default constructor" << endl;
        size = 0;
        buf = new char[size + 1];
        *(buf + size) = '\0';
    }
    MyString(char *_inputString)
    {
        size = strlen(_inputString);
        buf = new char[size + 1];
        strncpy(buf, _inputString, size);
        *(buf + size) = '\0';
    }
    MyString(MyString& iString)
    {
        //cout << "Copy constructor called" << endl;
        size = iString.length();
        this->buf = new char[size + 1];
        strcpy(buf, iString.buf);
        *(buf + size) = '\0';
    }
    // Move copy constructor
    MyString(MyString&& iString)
    {
        cout << "Move copy constructor called" << endl;
        size = iString.length();
        this->buf = iString.buf;
        iString.buf = nullptr;
        // delete iString;
    }
    MyString& operator+(MyString& iString)
    {
        //  cout << "+ operator" << endl;
        int len = iString.length() + this->length();
        MyString *temp = new MyString;
        delete []temp->buf;
        temp->buf = new char[len + 1];
        strncpy(temp->buf, this->buf, this->length());
        strncat(temp->buf, (const char *)iString.buf, 
                iString.length());
        *(temp->buf + len) = '\0';
        //cout << "+ operator end" << endl;
        return (*temp);
    }
    ~MyString()
    {
        //cout << "string destructor" << endl;
        delete []buf;
    }
    // Move assignment operator
    MyString& operator=(MyString& iString)
    {
        //cout << "Assignment operator" << endl;
        delete []buf;
        size = iString.length();
        buf = new char[size + 1];
        strcpy(buf, iString.buf);
        *(buf + size) = '\0';
        return (*this);
    }
    MyString& operator=(MyString&& iString)
    {
        //cout << "Move assignment operator called" << endl;
        delete []buf;
        size = iString.length();
        this->buf = iString.buf;
        iString.buf = nullptr;
        return (*this);
    }

    friend ostream& operator<<(ostream& os, MyString& _str)
    {
        os << _str.buf;
        return os;
    }
    int length()
    {
        return size;
    }
private:
    char* buf;
    int size;
};


class RefCount
{
 public:
    RefCount():mRefCount(0)
    {
    }
    void acquire()
    {
        mRefCount++;
    }
    int release()
    {
        return --mRefCount;
    }
    int& operator*()
    {
        return mRefCount;
    }
    int getValue()
    {
        return mRefCount;
    }
 private:
    int mRefCount;
};

template <class T>
class MySmartP
{
public:
    MySmartP()
    {
        mPtr = new T;
        mRefCount = new RefCount;
        mRefCount->acquire();
    }
    MySmartP(T *ptr)
    {
        mPtr = ptr;
        mRefCount = new RefCount;
        mRefCount->acquire();
    }
    MySmartP(MySmartP& smartPtr)
    {
        mPtr = smartPtr.mPtr;
        mRefCount = smartPtr.mRefCount;
        mRefCount->acquire();
    }
    ~MySmartP()
    {
        if (mRefCount->release() == 0)
        {
            delete mRefCount;
            delete mPtr;
        }
    }
    MySmartP& operator=(MySmartP& smartPtr)
    {
        if (mRefCount->release() == 0)
        {
            delete mRefCount;
            delete mPtr;
        }
        mPtr = smartPtr.mPtr;
        mRefCount = smartPtr.mRefCount;
        mRefCount->acquire();
        return (*this);
    }
    int refCount()
    {
        return mRefCount->getValue();
    }
    T* get()
    {
        if (mRefCount->getValue() > 0)
        {
            return mPtr;
        }
        else
        {
            return NULL;
        }
    }
    T& operator*()
    {
        return *mPtr;
    }
    T* operator->()
    {
        return mPtr;
    }
private:
    RefCount* mRefCount;
    T*     mPtr;
};

int main ()
{
    {
        MyString *intP = new MyString("Snehasish");
        MySmartP<MyString> p(intP);
        cout << "value " << *p.get() << " refCou " << p.refCount() << endl;
        {
            MySmartP<MyString> q(p);
            cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
            cout << "q value " << *q.get() << " refCou " << q.refCount() << endl;
        }
        cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
        {
            MySmartP<MyString> q;
            cout << "q value " << *q.get() << " refCou " << q.refCount() << endl;
            q = p;
            cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
            cout << "q value " << *q.get() << " refCou " << q.refCount() << endl;
        }
        cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
        cout << "p length " << p->length() << endl;
    }
    {
        int *intP = new int(11);
        MySmartP<int> p(intP);
        cout << "value " << *p.get() << " refCou " << p.refCount() << endl;
        {
            MySmartP<int> q(p);
            cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
            cout << "q value " << *q.get() << " refCou " << q.refCount() << endl;
        }
        cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
        {
            MySmartP<int> q;
            cout << "q value " << *q.get() << " refCou " << q.refCount() << endl;
            q = p;
            cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
            cout << "q value " << *q.get() << " refCou " << q.refCount() << endl;
        }
        cout << "p value " << *p.get() << " refCou " << p.refCount() << endl;
    }
        
    return 0;
}
