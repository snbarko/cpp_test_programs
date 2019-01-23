#include <iostream>

class Point
{
public:
    Point(int _x = 0, int _y = 0): x(_x), y(_y)
    {
    }
private:
    int x;
    int y;
};

class Circle
{
public:
    // Circle(int _x = 0, int _y = 0, int _r = 0):Point(_x, _y), radius(_r)
    // {
        
    // }
    Circle(int _x = 0, int _y = 0, int _r = 0) : centre(_x, _y), radius(_r)
    {
    }
private:
    Point centre;
    int radius;
};

int main()
{
    Point P(1,2);
    Circle C(1,2,3);
    return 0;
}
