#include <iostream>
#include <string.h>

class Shape
{
public:
    Shape(char *_name)
    {
        strncpy(name, _name, 19);
        name[19] = '\0';
    }
    virtual double area() = 0;
    char *whatAmI()
    {
        return name;
    }
private:
    char name[20];
};

class Rectangle : public Shape
{
public:
    Rectangle(int _len, int _bre): Shape("Rectangle"), len(_len), bre(_bre)
    {
    }
    virtual double area()
    {
        return len * bre;
    }
private:
    int len;
    int bre;
};

class Square : public Shape
{
public:
    Square(int _len) : Shape("Square"), len(_len)
    {
    }
    virtual double area()
    {
        return len * len;
    }
private:
    int len;
};

int main()
{
    Shape *s = new Rectangle(10,55);
    std::cout << s->whatAmI() << " area : " << s->area() << std::endl;
    Shape *r = new Square(11);
    std::cout << r->whatAmI() << " area : " << r->area() << std::endl;

    return 0;
}
