#include "trapeze.h"
#include <cmath>


Trapeze::Trapeze(const Point& a, const Point& b, const Point& c, const Point& d){
    p1 = a;
    p2 = b;
    p3 = c;
    p4 = d;
}

Trapeze::Trapeze(const Trapeze& other){
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    p4 = other.p4;
}

Trapeze::Trapeze(Trapeze&& other){
    p1 = std::move(other.p1); 
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    other.p1 = Point(0, 0);
    other.p2 = Point(0, 0);
    other.p3 = Point(0, 0);
    other.p4 = Point(0, 0);
} 

Point Trapeze::geometricCenter() const {
    double center_x = (p1.get_X() + p2.get_X() + p3.get_X() + p4.get_X()) / 4.0;
    double center_y = (p1.get_Y() + p2.get_Y() + p3.get_Y() + p4.get_Y()) / 4.0;
    return Point(center_x, center_y);
}

Trapeze::operator double() const {   
    double base1 = std::sqrt(std::pow(p2.get_X() - p1.get_X(), 2) + 
                            std::pow(p2.get_Y() - p1.get_Y(), 2));
    double base2 = std::sqrt(std::pow(p4.get_X() - p3.get_X(), 2) + 
                            std::pow(p4.get_Y() - p3.get_Y(), 2));

    Point mid1((p1.get_X() + p2.get_X()) / 2, (p1.get_Y() + p2.get_Y()) / 2);
    Point mid2((p3.get_X() + p4.get_X()) / 2, (p3.get_Y() + p4.get_Y()) / 2);

    double height = std::sqrt(std::pow(mid2.get_X() - mid1.get_X(), 2) + 
                            std::pow(mid2.get_Y() - mid1.get_Y(), 2));

    return (base1 + base2) * height / 2.0;
}

bool Trapeze::operator==(const Figure& other) const {
    const Trapeze& otherTrapeze = static_cast<const Trapeze&>(other);
    return p1 == otherTrapeze.p1 && p2 == otherTrapeze.p2 && 
           p3 == otherTrapeze.p3 && p4 == otherTrapeze.p4;
}

Figure& Trapeze::operator=(const Figure& other) {
    const Trapeze& otherTrapeze = static_cast<const Trapeze&>(other);
    p1 = otherTrapeze.p1;  
    p2 = otherTrapeze.p2;
    p3 = otherTrapeze.p3;
    p4 = otherTrapeze.p4;
    return *this;
}

Figure& Trapeze::operator=(Figure&& other){
    Trapeze& otherTrapeze = static_cast<Trapeze&>(other);
    
    p1 = std::move(otherTrapeze.p1);
    p2 = std::move(otherTrapeze.p2);
    p3 = std::move(otherTrapeze.p3);
    p4 = std::move(otherTrapeze.p4);

    otherTrapeze.p1 = Point(0, 0);
    otherTrapeze.p2 = Point(0, 0);
    otherTrapeze.p3 = Point(0, 0);
    otherTrapeze.p4 = Point(0, 0);

    return *this;
}

std::ostream& Trapeze::output(std::ostream& os) const
{
    os << "Trapeze: " << p1.get_X() << " " << p1.get_Y() << " "
        << p2.get_X() << " " << p2.get_Y() << " "
        << p3.get_X() << " " << p3.get_Y() << " "
        << p4.get_X() << " " << p4.get_Y();
    return os;
}

std::istream& Trapeze::input(std::istream& is){
    double x1, y1, x2, y2, x3, y3, x4, y4;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    p1 = Point(x1, y1);
    p2 = Point(x2, y2);
    p3 = Point(x3, y3);
    p4 = Point(x4, y4);

    return is;
}

Trapeze& Trapeze::operator=(const Trapeze& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

Trapeze& Trapeze::operator=(Trapeze&& other) {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
        other.p1 = Point(0, 0);
        other.p2 = Point(0, 0);
        other.p3 = Point(0, 0);
        other.p4 = Point(0, 0);
    }
    return *this;
}