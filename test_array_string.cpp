#include <iostream>
#include <string.h>

using namespace std;

class MyException : public exception
{
public:
    MyException(char* msg)
    {
        message = new char[strlen(msg) + 1];
        strncpy(message, msg, strlen(msg));
        message[strlen(msg)] = '\0';
    }
    virtual ~MyException() throw()
    {
        delete message;
    }
    char* what()
    {
        return message;
    }
private:
    char* message;
};

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
    char& operator[](int idx)
    {
        if (idx >= size)
        {
            throw MyException("Out of bould string access");
        }
        return buf[idx];
    }
    MyString& operator++(int a)
    {
        for (int i = 0; i < size;i++)
        {
            ++buf[i];
            
        }
    }
    friend MyString& operator++(MyString& str)
    {
        for (int i = 0; i < str.size;i++)
        {
            ++str.buf[i];
            
        }
    }
    friend MyString& operator--(MyString& str)
    {
        for (int i = 0; i < str.size;i++)
        {
            --str.buf[i];
            
        }
    }
    MyString& operator--(int a)
    {
        for (int i = 0; i < size;i++)
        {
            --buf[i];
            
        }
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

class Array
{
public:
    Array(int size):mSize(size)
    {
        mStrings = new MyString[size];
    }
    MyString& operator[](int idx)
    {
        if (idx >= mSize)
        {
            throw MyException("Out of bould array access.");
        }
        return mStrings[idx];
    }
private:
    MyString* mStrings;
    int mSize;
};

int main()
{
    MyString s1("Snehasish");
    Array a1(10);
    a1[0] = "Banerjee";
    a1[1] = "Hewlett";
    a1[2] = "Packard";
    cout << a1[0] << endl;
    cout << a1[0][1] << endl;
    try
    {
        cout << a1[0][100] << endl;
    }
    catch(MyException& ex)
    {
        cout << ex.what() << endl;
    }
    try
    {
        cout << a1[10] << endl;
    }
    catch(MyException& ex)
    {
        cout << ex.what() << endl;
    }
    // {
    //     MyString *s2 = &a1[0];
    //     cout << *s2 << endl;
    //     s2++;
    //     cout << *s2 << endl;
    // }
    {
        MyString s2 = a1[0];
        cout << s2 << endl;
        s2++;
        cout << "after post inc op " << s2 << endl;
        s2--;
        cout << "after post dec op " << s2 << endl;
        ++s2;
        cout << "after pre inc op  " << s2 << endl;
        --s2;
        cout << "after post dec op  " << s2 << endl;
    }

    return 0;
}
