// ostringstream::rdbuf
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream

int main () {
    std::ostringstream oss;
    oss << "One hundred and one";
    // std::string s = oss.str();
    // std::cout << s << '\n';
    // const char* ptr = s.c_str();
    const char* ptr = oss.str().c_str();
    std::cout << "snb " << ptr << std::endl;
    for (size_t i=0; i < oss.str().length() + 1; i++)
    {
        std::cout << *(ptr+i) << std::endl;
        if (*(ptr + i) == '\0')
            std::cout << "I got a NULL!!" << std::endl;
    }
    // std::copy()
    return 0;
}
