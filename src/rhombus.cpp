#include "rhombus.h"
#include <cmath>

Rhombus::Rhombus(const Point& a, const Point& b, const Point& c, const Point& d){
    p1 = a;
    p2 = b;
    p3 = c;
    p4 = d;
}

Rhombus::Rhombus(const Rhombus& other){
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    p4 = other.p4;
}

Rhombus::Rhombus(Rhombus&& other){
    p1 = std::move(other.p1); 
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    other.p1 = Point(0, 0);
    other.p2 = Point(0, 0);
    other.p3 = Point(0, 0);
    other.p4 = Point(0, 0);
} 

Point Rhombus::geometricCenter() const {
    double center_x = (p1.get_X() + p2.get_X() + p3.get_X() + p4.get_X()) / 4.0;
    double center_y = (p1.get_Y() + p2.get_Y() + p3.get_Y() + p4.get_Y()) / 4.0;
    return Point(center_x, center_y);
}

Rhombus::operator double() const {   
    double d1 = std::sqrt(std::pow(p3.get_X() - p1.get_X(), 2) + 
                         std::pow(p3.get_Y() - p1.get_Y(), 2));
                         
    double d2 = std::sqrt(std::pow(p4.get_X() - p2.get_X(), 2) + 
                         std::pow(p4.get_Y() - p2.get_Y(), 2));
    
    return (d1 * d2) / 2.0;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    if (!otherRhombus) return false;
    
    return p1 == otherRhombus->p1 && p2 == otherRhombus->p2 && 
           p3 == otherRhombus->p3 && p4 == otherRhombus->p4;
}

Figure& Rhombus::operator=(const Figure& other) {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    if (!otherRhombus) return *this;
    
    p1 = otherRhombus->p1;  
    p2 = otherRhombus->p2;
    p3 = otherRhombus->p3;
    p4 = otherRhombus->p4;
    return *this;
}

Figure& Rhombus::operator=(Figure&& other){
    Rhombus* otherRhombus = dynamic_cast<Rhombus*>(&other);
    if (!otherRhombus) return *this;
    
    p1 = std::move(otherRhombus->p1);
    p2 = std::move(otherRhombus->p2);
    p3 = std::move(otherRhombus->p3);
    p4 = std::move(otherRhombus->p4);

    otherRhombus->p1 = Point(0, 0);
    otherRhombus->p2 = Point(0, 0);
    otherRhombus->p3 = Point(0, 0);
    otherRhombus->p4 = Point(0, 0);

    return *this;
}

std::ostream& Rhombus::output(std::ostream& os) const
{
    os << "Rhombus: " << p1.get_X() << " " << p1.get_Y() << " "
       << p2.get_X() << " " << p2.get_Y() << " "
       << p3.get_X() << " " << p3.get_Y() << " "
       << p4.get_X() << " " << p4.get_Y();
    return os;
}

std::istream& Rhombus::input(std::istream& is){
    double x1, y1, x2, y2, x3, y3, x4, y4;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    p1 = Point(x1, y1);
    p2 = Point(x2, y2);
    p3 = Point(x3, y3);
    p4 = Point(x4, y4);

    return is;
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) {
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