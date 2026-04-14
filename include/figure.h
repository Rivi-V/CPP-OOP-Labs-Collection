#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <iostream>
#include <concepts>

template<Scalar T>
class Figure {
public:
    Figure() = default;
    virtual ~Figure() = default;

    virtual Figure<T>& operator=(const Figure<T>& other) = 0; 
    virtual Figure<T>& operator=(Figure<T>&& other) = 0; 
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    
    virtual Point<T> geometricCenter() const = 0; 
    virtual operator double() const = 0;  
    
    virtual std::ostream& output(std::ostream& os) const = 0;
    virtual std::istream& input(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        return fig.output(os);
    }
    
    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        return fig.input(is);
    }
};

#endif