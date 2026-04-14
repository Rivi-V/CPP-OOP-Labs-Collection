#ifndef TRAPEZE_H
#define TRAPEZE_H

#include "figure.h"
#include "point.h"
#include <iostream> 

class Trapeze : public Figure
{
public:
    Trapeze() = default;
    
    Trapeze(const Point& a, const Point& b, const Point& c, const Point& d);
    Trapeze(const Trapeze& other); 
    Trapeze(Trapeze&& other);
    Trapeze& operator=(const Trapeze& other);
    Trapeze& operator=(Trapeze&& other);
    ~Trapeze() = default;  
    

    Point geometricCenter() const override;
    operator double() const override;
    bool operator==(const Figure& other) const override;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) override;

    std::ostream& output(std::ostream& os) const override;
    std::istream& input(std::istream& is) override;

    Point get_p1() const { return p1; }
    Point get_p2() const { return p2; }
    Point get_p3() const { return p3; }
    Point get_p4() const { return p4; }

private:
    Point p1{0, 0};
    Point p2{0, 0};
    Point p3{0, 0};
    Point p4{0, 0};
};

#endif