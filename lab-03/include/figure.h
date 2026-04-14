#ifndef FIGURE_H
#define FIGURE_H

#include <point.h>

class Figure
{
public:
    Figure() = default;

    virtual Figure& operator=(const Figure& other) = 0; 
    virtual Figure& operator=(Figure&& other) = 0; 
    
    virtual ~Figure() = default;
    
    virtual bool operator==(const Figure& other) const = 0;
    
    virtual Point geometricCenter() const = 0; 
    virtual operator double() const = 0;  
    
    virtual std::ostream& output(std::ostream& os) const = 0;
    virtual std::istream& input(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};

#endif 

