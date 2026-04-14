#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"
#include "point.h"
#include <iostream>
#include <memory>
#include <cmath>

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() {
        p1 = std::make_unique<Point<T>>(0, 0);
        p2 = std::make_unique<Point<T>>(0, 0);
        p3 = std::make_unique<Point<T>>(0, 0);
    }
    
    Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        p1 = std::make_unique<Point<T>>(a);
        p2 = std::make_unique<Point<T>>(b);
        p3 = std::make_unique<Point<T>>(c);
    }
    
    Triangle(const Triangle<T>& other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
    }
    
    Triangle(Triangle<T>&& other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
    }
    
    Triangle<T>& operator=(const Triangle<T>& other) {
        if (this != &other) {
            p1 = std::make_unique<Point<T>>(*other.p1);
            p2 = std::make_unique<Point<T>>(*other.p2);
            p3 = std::make_unique<Point<T>>(*other.p3);
        }
        return *this;
    }
    
    Triangle<T>& operator=(Triangle<T>&& other) {
        if (this != &other) {
            p1 = std::move(other.p1);
            p2 = std::move(other.p2);
            p3 = std::move(other.p3);
        }
        return *this;
    }
    
    ~Triangle() = default;
    
    Point<T> geometricCenter() const override {
        T center_x = (p1->get_X() + p2->get_X() + p3->get_X()) / 3.0;
        T center_y = (p1->get_Y() + p2->get_Y() + p3->get_Y()) / 3.0;
        return Point<T>(center_x, center_y);
    }
    
    operator double() const override {
        double area = std::abs(
            (p1->get_X() * (p2->get_Y() - p3->get_Y()) +
             p2->get_X() * (p3->get_Y() - p1->get_Y()) +
             p3->get_X() * (p1->get_Y() - p2->get_Y())) / 2.0
        );
        return area;
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Triangle<T>* otherTriangle = dynamic_cast<const Triangle<T>*>(&other);
        if (!otherTriangle) return false;
        
        return *p1 == *(otherTriangle->p1) && 
               *p2 == *(otherTriangle->p2) && 
               *p3 == *(otherTriangle->p3);
    }
    
    Figure<T>& operator=(const Figure<T>& other) override {
        const Triangle<T>* otherTriangle = dynamic_cast<const Triangle<T>*>(&other);
        if (!otherTriangle) return *this;
        
        p1 = std::make_unique<Point<T>>(*otherTriangle->p1);
        p2 = std::make_unique<Point<T>>(*otherTriangle->p2);
        p3 = std::make_unique<Point<T>>(*otherTriangle->p3);
        return *this;
    }
    
    Figure<T>& operator=(Figure<T>&& other) override {
        Triangle<T>* otherTriangle = dynamic_cast<Triangle<T>*>(&other);
        if (!otherTriangle) return *this;
        
        p1 = std::move(otherTriangle->p1);
        p2 = std::move(otherTriangle->p2);
        p3 = std::move(otherTriangle->p3);
        return *this;
    }

    std::ostream& output(std::ostream& os) const override {
        os << "Triangle: " 
           << p1->get_X() << " " << p1->get_Y() << " "
           << p2->get_X() << " " << p2->get_Y() << " "
           << p3->get_X() << " " << p3->get_Y();
        return os;
    }
    
    std::istream& input(std::istream& is) override {
        T x1, y1, x2, y2, x3, y3;
        is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        p1 = std::make_unique<Point<T>>(x1, y1);
        p2 = std::make_unique<Point<T>>(x2, y2);
        p3 = std::make_unique<Point<T>>(x3, y3);

        return is;
    }

    Point<T> get_p1() const { return *p1; }
    Point<T> get_p2() const { return *p2; }
    Point<T> get_p3() const { return *p3; }

private:
    std::unique_ptr<Point<T>> p1, p2, p3;
};

#endif