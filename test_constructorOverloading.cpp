#include <iostream>
#include <string.h>

using namespace std;

class MyString
{
public:
    MyString()
    {
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
        size = iString.length();
        this->buf = new char[size + 1];
        strcpy(buf, iString.buf);
        *(buf + size) = '\0';
    }
    // Move copy constructor
    MyString(MyString&& iString)
    {
        size = iString.length();
        this->buf = iString.buf;
        iString.buf = nullptr;
        // delete iString;
    }
    MyString& operator+(MyString& iString)
    {
        int len = iString.length() + this->length();
        MyString *temp = new MyString;
        delete []temp->buf;
        temp->buf = new char[len + 1];
        strncpy(temp->buf, this->buf, this->length());
        strncat(temp->buf, (const char *)iString.buf, iString.length());
        *(temp->buf + size) = '\0';
        return (*temp);
    }
    ~MyString()
    {
        delete []buf;
    }
    // Move assignment operator
    MyString& operator=(MyString& iString)
    {
        delete []buf;
        size = iString.length();
        buf = new char[size + 1];
        strcpy(buf, iString.buf);
        *(buf + size) = '\0';
    }
    MyString& operator=(MyString&& iString)
    {
        delete []buf;
        size = iString.length();
        this->buf = iString.buf;
        iString.buf = nullptr;
    }

    friend ostream& operator<<(ostream& os, MyString& _str)
    {
        os << _str.buf << endl;
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

int main()
{
    MyString str("SNB");
    MyString str2(str);
    cout << "str " << str;
    str2 = str;
    cout << "str2 " << str2;
    MyString str3(" HPE");
    cout << "str3 " << str3;
    MyString str4;
    str4 = str2 + str3;
    cout << "str4 " << str4;
    MyString str5 = str4 + str;
    cout << "str5 " << str5;
    return 0;
}
