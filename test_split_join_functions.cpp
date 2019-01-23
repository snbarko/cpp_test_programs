#include <iostream>
#include <string.h>

class MyString
{
public:
    MyString(char* _inputString): mInputString(_inputString)
    {
        mStringLen = strlen(_inputString);
    }
    void splitString(char _delimeter)
    {
        mSplitedStrings = new char*[mStringLen];
        int j = 0;
        for (int i = 0;i < mStringLen;i++)
        {
            if (mInputString[i] == _delimeter)
            {
                
            }
            mSplitedStrings[j]
        }
    }
private:
    char* mInputString;
    char** mSplitedStrings;
    int mStringLen;
};

int main()
{
    MyString("ABC DEF");
    return 0;
}
