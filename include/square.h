#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"
#include "point.h"
#include <iostream>
#include <memory>
#include <cmath>

template<Scalar T>
class Square : public Figure<T> {
public:
    Square() {
        p1 = std::make_unique<Point<T>>(0, 0);
        p2 = std::make_unique<Point<T>>(0, 0);
        p3 = std::make_unique<Point<T>>(0, 0);
        p4 = std::make_unique<Point<T>>(0, 0);
    }
    
    Square(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        p1 = std::make_unique<Point<T>>(a);
        p2 = std::make_unique<Point<T>>(b);
        p3 = std::make_unique<Point<T>>(c);
        p4 = std::make_unique<Point<T>>(d);
    }
    
    Square(const Square<T>& other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    
    Square(Square<T>&& other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    
    Square<T>& operator=(const Square<T>& other) {
        if (this != &other) {
            p1 = std::make_unique<Point<T>>(*other.p1);
            p2 = std::make_unique<Point<T>>(*other.p2);
            p3 = std::make_unique<Point<T>>(*other.p3);
            p4 = std::make_unique<Point<T>>(*other.p4);
        }
        return *this;
    }
    
    Square<T>& operator=(Square<T>&& other) {
        if (this != &other) {
            p1 = std::move(other.p1);
            p2 = std::move(other.p2);
            p3 = std::move(other.p3);
            p4 = std::move(other.p4);
        }
        return *this;
    }
    
    ~Square() = default;
    
    Point<T> geometricCenter() const override {
        T center_x = (p1->get_X() + p2->get_X() + p3->get_X() + p4->get_X()) / 4.0;
        T center_y = (p1->get_Y() + p2->get_Y() + p3->get_Y() + p4->get_Y()) / 4.0;
        return Point<T>(center_x, center_y);
    }
    
    operator double() const override {
        // Вычисляем длину стороны (расстояние между двумя соседними точками)
        double side = std::sqrt(std::pow(p2->get_X() - p1->get_X(), 2) + 
                               std::pow(p2->get_Y() - p1->get_Y(), 2));
        
        return side * side;
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Square<T>* otherSquare = dynamic_cast<const Square<T>*>(&other);
        if (!otherSquare) return false;
        
        return *p1 == *(otherSquare->p1) && 
               *p2 == *(otherSquare->p2) && 
               *p3 == *(otherSquare->p3) && 
               *p4 == *(otherSquare->p4);
    }
    
    Figure<T>& operator=(const Figure<T>& other) override {
        const Square<T>* otherSquare = dynamic_cast<const Square<T>*>(&other);
        if (!otherSquare) return *this;
        
        p1 = std::make_unique<Point<T>>(*otherSquare->p1);
        p2 = std::make_unique<Point<T>>(*otherSquare->p2);
        p3 = std::make_unique<Point<T>>(*otherSquare->p3);
        p4 = std::make_unique<Point<T>>(*otherSquare->p4);
        return *this;
    }
    
    Figure<T>& operator=(Figure<T>&& other) override {
        Square<T>* otherSquare = dynamic_cast<Square<T>*>(&other);
        if (!otherSquare) return *this;
        
        p1 = std::move(otherSquare->p1);
        p2 = std::move(otherSquare->p2);
        p3 = std::move(otherSquare->p3);
        p4 = std::move(otherSquare->p4);
        return *this;
    }

    std::ostream& output(std::ostream& os) const override {
        os << "Square: " 
           << p1->get_X() << " " << p1->get_Y() << " "
           << p2->get_X() << " " << p2->get_Y() << " "
           << p3->get_X() << " " << p3->get_Y() << " "
           << p4->get_X() << " " << p4->get_Y();
        return os;
    }
    
    std::istream& input(std::istream& is) override {
        T x1, y1, x2, y2, x3, y3, x4, y4;
        is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        p1 = std::make_unique<Point<T>>(x1, y1);
        p2 = std::make_unique<Point<T>>(x2, y2);
        p3 = std::make_unique<Point<T>>(x3, y3);
        p4 = std::make_unique<Point<T>>(x4, y4);

        return is;
    }

    Point<T> get_p1() const { return *p1; }
    Point<T> get_p2() const { return *p2; }
    Point<T> get_p3() const { return *p3; }
    Point<T> get_p4() const { return *p4; }

private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4;
};

#endif