#include "pentagon.h"
#include <cmath>

Pentagon::Pentagon(const Point& a, const Point& b, const Point& c, const Point& d, const Point& e){
    p1 = a;
    p2 = b;
    p3 = c;
    p4 = d;
    p5 = e;
}

Pentagon::Pentagon(const Pentagon& other){
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    p4 = other.p4;
    p5 = other.p5;
}

Pentagon::Pentagon(Pentagon&& other){
    p1 = std::move(other.p1); 
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    other.p1 = Point(0, 0);
    other.p2 = Point(0, 0);
    other.p3 = Point(0, 0);
    other.p4 = Point(0, 0);
    other.p5 = Point(0, 0);
} 

Point Pentagon::geometricCenter() const {
    double center_x = (p1.get_X() + p2.get_X() + p3.get_X() + p4.get_X() + p5.get_X()) / 5.0;
    double center_y = (p1.get_Y() + p2.get_Y() + p3.get_Y() + p4.get_Y() + p5.get_Y()) / 5.0;
    return Point(center_x, center_y);
}

Pentagon::operator double() const {   
    double sum1 = p1.get_X() * p2.get_Y() + 
                  p2.get_X() * p3.get_Y() + 
                  p3.get_X() * p4.get_Y() + 
                  p4.get_X() * p5.get_Y() + 
                  p5.get_X() * p1.get_Y();
    
    double sum2 = p1.get_Y() * p2.get_X() + 
                  p2.get_Y() * p3.get_X() + 
                  p3.get_Y() * p4.get_X() + 
                  p4.get_Y() * p5.get_X() + 
                  p5.get_Y() * p1.get_X();
    
    return std::abs(sum1 - sum2) / 2.0;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    if (!otherPentagon) return false;
    
    return p1 == otherPentagon->p1 && 
           p2 == otherPentagon->p2 && 
           p3 == otherPentagon->p3 && 
           p4 == otherPentagon->p4 && 
           p5 == otherPentagon->p5;
}

Figure& Pentagon::operator=(const Figure& other) {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    if (!otherPentagon) return *this;
    
    p1 = otherPentagon->p1;  
    p2 = otherPentagon->p2;
    p3 = otherPentagon->p3;
    p4 = otherPentagon->p4;
    p5 = otherPentagon->p5;
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) {
    Pentagon* otherPentagon = dynamic_cast<Pentagon*>(&other);
    if (!otherPentagon) return *this;
    
    p1 = std::move(otherPentagon->p1);
    p2 = std::move(otherPentagon->p2);
    p3 = std::move(otherPentagon->p3);
    p4 = std::move(otherPentagon->p4);
    p5 = std::move(otherPentagon->p5);

    otherPentagon->p1 = Point(0, 0);
    otherPentagon->p2 = Point(0, 0);
    otherPentagon->p3 = Point(0, 0);
    otherPentagon->p4 = Point(0, 0);
    otherPentagon->p5 = Point(0, 0);

    return *this;
}

std::ostream& Pentagon::output(std::ostream& os) const
{
    os << "Pentagon: " << p1.get_X() << " " << p1.get_Y() << " "
       << p2.get_X() << " " << p2.get_Y() << " "
       << p3.get_X() << " " << p3.get_Y() << " "
       << p4.get_X() << " " << p4.get_Y() << " "
       << p5.get_X() << " " << p5.get_Y();
    return os;
}

std::istream& Pentagon::input(std::istream& is){
    double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;

    p1 = Point(x1, y1);
    p2 = Point(x2, y2);
    p3 = Point(x3, y3);
    p4 = Point(x4, y4);
    p5 = Point(x5, y5);

    return is;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
        p5 = other.p5;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
        p5 = std::move(other.p5);
        other.p1 = Point(0, 0);
        other.p2 = Point(0, 0);
        other.p3 = Point(0, 0);
        other.p4 = Point(0, 0);
        other.p5 = Point(0, 0);
    }
    return *this;
}