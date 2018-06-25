// #include <iostream>

namespace abc {
class a {
public:
    void member_function_a(int number);
};
};

namespace abc {
enum def {
    ONE=1,
    TWO,
    THREE,
};
};

void abc::a::member_function_a(int number)
{
    std::cout << "This is member function of a" << std::endl;
    if (number == abc::TWO) {
        std::cout << "You lucky !! You got 2." << std::endl;
    } else if (number == THREE) {
           std::cout << "You unlucky !! You got 3." << std::endl;
    }
}

int main()
{
    abc::a obj;
    obj.member_function_a(2);
    obj.member_function_a(3);
    return 0;
}
