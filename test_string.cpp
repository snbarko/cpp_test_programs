#include <iostream>
#include <string.h>

using namespace std;

class List;

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
    

    List& split();

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

class Node
{
public:
    Node(char *_str):str(_str), next(nullptr)
    {
    }
    ~Node()
    {
        //cout << "Node destructor" << endl;
    }
    Node *next;
    MyString& getString()
    {
        return str;
    }
    friend ostream& operator<<(ostream& os, Node& nd)
    {
        os << nd.str;
        return os;
    }
private:
    MyString str;
};

class List
{
public:
    List(): head(nullptr), count(0)
    {
    }
    ~List()
    {
        //cout << "List destructor called" << endl;
        if (head == nullptr)
        {
            return;
        }
        Node* tmpNode = head;
        while (tmpNode != nullptr)
        {
            Node* tmpNode1 = tmpNode->next;
            delete tmpNode;
            tmpNode = tmpNode1;
        }
    }
    Node& operator[](int idx)
    {
        //cout << "operator overloaded" << endl;
        // if (head == nullptr)
        // {
        //     throw;
        //     return nullptr;
        // }
        Node* tmpNode = head;
        int i = 0;
        while ((tmpNode != nullptr) && (i < idx))
        {
            tmpNode = tmpNode->next;
            i++;
        }
        return (*tmpNode);
    }
    void append(char *_str)
    {
        Node* newNode = new Node(_str);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* tmpNode = head;
            while (tmpNode->next != nullptr)
            {
                tmpNode = tmpNode->next;
            }
            tmpNode->next = newNode;
        }
        count++;
    }
    friend ostream& operator<<(ostream& os, List& lst)
    {
        os << "List->";
        if (lst.getHead() == nullptr)
        {
            os << "No elements present in list" << endl;
            return os;
        }
        Node* tmpNode = lst.getHead();
        int i = 1;
        while (tmpNode != nullptr)
        {
            os << *tmpNode << "->";
            tmpNode = tmpNode->next;
            i++;
        }
        os << "nullptr" << endl;
        return os;
    }
    int size() { return count; }
    Node* getHead() { return head; }
private:
    Node *head;
    int count;
};

List& MyString::split()
{
    List* myList = new List;
    int startI = 0, endI = 0;
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (buf[i] == ' ')
        {
            endI = (i == 0) ? 0 : (i - 1);
            if (endI != 0)
            {
                buf[i] = '\0';
                myList->append(&buf[startI]);
                buf[i] = ' ';
            }
            startI = i + 1;
        }
    }
    if (startI < i)
    {
        myList->append(&buf[startI]);
    }
    return *myList;
}

int main()
{
    List mylist;
    mylist.append("Snehasish");
    cout << mylist << endl;
    mylist.append("Banerjee");
    cout << mylist << endl;
    for (int i = 0; i< mylist.size(); i++)
    {
        cout << "index " << i << " " << mylist[i] << endl;
    }

    MyString str("AA BB");
    List lst = move(str.split());
    cout << lst;

    {
        MyString str1("SNBSNB hi hello bye");
        List lst1 = move(str1.split());
        cout << lst1;
        for (int i = 0; i< lst1.size(); i++)
        {
            cout << "index " << i << " " << lst1[i] << endl;
        }
    }
    {
        MyString str1("SNBSNB hi hello bye");
        List lst1 = move(str1.split());
        cout << lst1;
        for (int i = 0; i< lst1.size(); i++)
        {
            cout << "index " << i << " " << lst1[i] << endl;
        }
    }
    {
        MyString str1(" SNBSNB hi hello bye");
        List lst1 = move(str1.split());
        cout << lst1;
        for (int i = 0; i< lst1.size(); i++)
        {
            cout << "index " << i << " " << lst1[i] << endl;
        }
    }
    {
        MyString str1(" SNBSNB hi hello bye ");
        List lst1 = move(str1.split());
        cout << lst1;
        for (int i = 0; i< lst1.size(); i++)
        {
            cout << "index " << i << " " << lst1[i] << endl;
        }
    }
    {
        MyString str1(" SNBSNB hi  hello bye ");
        List lst1 = move(str1.split());
        cout << lst1;
        for (int i = 0; i< lst1.size(); i++)
        {
            cout << "index " << i << " " << lst1[i] << endl;
        }
    }

    return 0;
}

// int main()
// {
//     MyString str = "SNB";
//     MyString str2(str);
//     cout << "str " << str;
//     str2 = str;
//     cout << "str2 " << str2;
//     MyString str3(" HPE");
//     cout << "str3 " << str3;
//     cout << "str add " << str2 + str3;
//     MyString str4 = move(str2 + str3);
//     cout << "str4 " << str4;
//     MyString str5;
//     str5 = move(str2 + str);
//     cout << "str5 " << str5;
//     return 0;
// }
