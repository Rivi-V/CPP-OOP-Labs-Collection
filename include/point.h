#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>;
Ё
template<Scalar T>
class Point
{
public:
    Point() = default;
    Point(T x, T y) : x_point(x), y_point(y) {}
    
    Point(const Point& other) = default;
    
    Point& operator=(const Point& other) = default;

    T get_X() const { return x_point; }
    T get_Y() const { return y_point; }
    void set_X(T x) { x_point = x; }
    void set_Y(T y) { y_point = y; }

    friend bool operator==(const Point& l_c, const Point& r_c) {
        return ((l_c.x_point == r_c.x_point) && (l_c.y_point == r_c.y_point));
    }

private:
    T x_point{0};
    T y_point{0};
};

#endif