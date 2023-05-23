#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <vector>


class Rectangle
{
private:
    int w , h;
    std::vector<float> verticesl 
public:
    Rectangle();
    Rectangle(int w, int h);

    ~Rectangle();
};

Rectangle::Rectangle() {}
Rectangle::Rectangle(int _w , int _h) {
    w = _w; h = _h;


}




Rectangle::~Rectangle(){}


#endif