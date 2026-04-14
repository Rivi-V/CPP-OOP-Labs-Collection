#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Point
{
public:
    Point() = default;
    Point(double x, double y) : x_point(x), y_point(y) {}
    
    Point(const Point& other) = default;
    
    Point& operator=(const Point& other) = default;

    double get_X() const { return x_point; }
    double get_Y() const { return y_point; }
    void set_X(double x) { x_point = x; }
    void set_Y(double y) { y_point = y; }

    friend bool operator==(const Point& l_c, const Point& r_c) {
        return ((l_c.x_point == r_c.x_point) && (l_c.y_point == r_c.y_point));
    }

private:
    double x_point{0};
    double y_point{0};
};

#endif