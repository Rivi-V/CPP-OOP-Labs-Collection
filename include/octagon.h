#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"
#include "point.h"
#include <iostream>
#include <memory>
#include <cmath>

template<Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() {
        p1 = std::make_unique<Point<T>>(0, 0);
        p2 = std::make_unique<Point<T>>(0, 0);
        p3 = std::make_unique<Point<T>>(0, 0);
        p4 = std::make_unique<Point<T>>(0, 0);
        p5 = std::make_unique<Point<T>>(0, 0);
        p6 = std::make_unique<Point<T>>(0, 0);
        p7 = std::make_unique<Point<T>>(0, 0);
        p8 = std::make_unique<Point<T>>(0, 0);
    }
    
    Octagon(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d, 
            const Point<T>& e, const Point<T>& f, const Point<T>& g, const Point<T>& h) {
        p1 = std::make_unique<Point<T>>(a);
        p2 = std::make_unique<Point<T>>(b);
        p3 = std::make_unique<Point<T>>(c);
        p4 = std::make_unique<Point<T>>(d);
        p5 = std::make_unique<Point<T>>(e);
        p6 = std::make_unique<Point<T>>(f);
        p7 = std::make_unique<Point<T>>(g);
        p8 = std::make_unique<Point<T>>(h);
    }
    
    Octagon(const Octagon<T>& other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
        p5 = std::make_unique<Point<T>>(*other.p5);
        p6 = std::make_unique<Point<T>>(*other.p6);
        p7 = std::make_unique<Point<T>>(*other.p7);
        p8 = std::make_unique<Point<T>>(*other.p8);
    }
    
    Octagon(Octagon<T>&& other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
        p5 = std::move(other.p5);
        p6 = std::move(other.p6);
        p7 = std::move(other.p7);
        p8 = std::move(other.p8);
    }
    
    Octagon<T>& operator=(const Octagon<T>& other) {
        if (this != &other) {
            p1 = std::make_unique<Point<T>>(*other.p1);
            p2 = std::make_unique<Point<T>>(*other.p2);
            p3 = std::make_unique<Point<T>>(*other.p3);
            p4 = std::make_unique<Point<T>>(*other.p4);
            p5 = std::make_unique<Point<T>>(*other.p5);
            p6 = std::make_unique<Point<T>>(*other.p6);
            p7 = std::make_unique<Point<T>>(*other.p7);
            p8 = std::make_unique<Point<T>>(*other.p8);
        }
        return *this;
    }
    
    Octagon<T>& operator=(Octagon<T>&& other) {
        if (this != &other) {
            p1 = std::move(other.p1);
            p2 = std::move(other.p2);
            p3 = std::move(other.p3);
            p4 = std::move(other.p4);
            p5 = std::move(other.p5);
            p6 = std::move(other.p6);
            p7 = std::move(other.p7);
            p8 = std::move(other.p8);
        }
        return *this;
    }
    
    ~Octagon() = default;
    
    Point<T> geometricCenter() const override {
        T center_x = (p1->get_X() + p2->get_X() + p3->get_X() + p4->get_X() + 
                      p5->get_X() + p6->get_X() + p7->get_X() + p8->get_X()) / 8.0;
        T center_y = (p1->get_Y() + p2->get_Y() + p3->get_Y() + p4->get_Y() + 
                      p5->get_Y() + p6->get_Y() + p7->get_Y() + p8->get_Y()) / 8.0;
        return Point<T>(center_x, center_y);
    }
    
    operator double() const override {
        double sum1 = p1->get_X() * p2->get_Y() + 
                      p2->get_X() * p3->get_Y() + 
                      p3->get_X() * p4->get_Y() + 
                      p4->get_X() * p5->get_Y() + 
                      p5->get_X() * p6->get_Y() +
                      p6->get_X() * p7->get_Y() +
                      p7->get_X() * p8->get_Y() +
                      p8->get_X() * p1->get_Y();
        
        double sum2 = p1->get_Y() * p2->get_X() + 
                      p2->get_Y() * p3->get_X() + 
                      p3->get_Y() * p4->get_X() + 
                      p4->get_Y() * p5->get_X() + 
                      p5->get_Y() * p6->get_X() +
                      p6->get_Y() * p7->get_X() +
                      p7->get_Y() * p8->get_X() +
                      p8->get_Y() * p1->get_X();
        
        return std::abs(sum1 - sum2) / 2.0;
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Octagon<T>* otherOctagon = dynamic_cast<const Octagon<T>*>(&other);
        if (!otherOctagon) return false;
        
        return *p1 == *(otherOctagon->p1) && 
               *p2 == *(otherOctagon->p2) && 
               *p3 == *(otherOctagon->p3) && 
               *p4 == *(otherOctagon->p4) && 
               *p5 == *(otherOctagon->p5) &&
               *p6 == *(otherOctagon->p6) &&
               *p7 == *(otherOctagon->p7) &&
               *p8 == *(otherOctagon->p8);
    }
    
    Figure<T>& operator=(const Figure<T>& other) override {
        const Octagon<T>* otherOctagon = dynamic_cast<const Octagon<T>*>(&other);
        if (!otherOctagon) return *this;
        
        p1 = std::make_unique<Point<T>>(*otherOctagon->p1);
        p2 = std::make_unique<Point<T>>(*otherOctagon->p2);
        p3 = std::make_unique<Point<T>>(*otherOctagon->p3);
        p4 = std::make_unique<Point<T>>(*otherOctagon->p4);
        p5 = std::make_unique<Point<T>>(*otherOctagon->p5);
        p6 = std::make_unique<Point<T>>(*otherOctagon->p6);
        p7 = std::make_unique<Point<T>>(*otherOctagon->p7);
        p8 = std::make_unique<Point<T>>(*otherOctagon->p8);
        return *this;
    }
    
    Figure<T>& operator=(Figure<T>&& other) override {
        Octagon<T>* otherOctagon = dynamic_cast<Octagon<T>*>(&other);
        if (!otherOctagon) return *this;
        
        p1 = std::move(otherOctagon->p1);
        p2 = std::move(otherOctagon->p2);
        p3 = std::move(otherOctagon->p3);
        p4 = std::move(otherOctagon->p4);
        p5 = std::move(otherOctagon->p5);
        p6 = std::move(otherOctagon->p6);
        p7 = std::move(otherOctagon->p7);
        p8 = std::move(otherOctagon->p8);
        return *this;
    }

    std::ostream& output(std::ostream& os) const override {
        os << "Octagon: " 
           << p1->get_X() << " " << p1->get_Y() << " "
           << p2->get_X() << " " << p2->get_Y() << " "
           << p3->get_X() << " " << p3->get_Y() << " "
           << p4->get_X() << " " << p4->get_Y() << " "
           << p5->get_X() << " " << p5->get_Y() << " "
           << p6->get_X() << " " << p6->get_Y() << " "
           << p7->get_X() << " " << p7->get_Y() << " "
           << p8->get_X() << " " << p8->get_Y();
        return os;
    }
    
    std::istream& input(std::istream& is) override {
        T x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
        is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 
           >> x5 >> y5 >> x6 >> y6 >> x7 >> y7 >> x8 >> y8;

        p1 = std::make_unique<Point<T>>(x1, y1);
        p2 = std::make_unique<Point<T>>(x2, y2);
        p3 = std::make_unique<Point<T>>(x3, y3);
        p4 = std::make_unique<Point<T>>(x4, y4);
        p5 = std::make_unique<Point<T>>(x5, y5);
        p6 = std::make_unique<Point<T>>(x6, y6);
        p7 = std::make_unique<Point<T>>(x7, y7);
        p8 = std::make_unique<Point<T>>(x8, y8);

        return is;
    }

    Point<T> get_p1() const { return *p1; }
    Point<T> get_p2() const { return *p2; }
    Point<T> get_p3() const { return *p3; }
    Point<T> get_p4() const { return *p4; }
    Point<T> get_p5() const { return *p5; }
    Point<T> get_p6() const { return *p6; }
    Point<T> get_p7() const { return *p7; }
    Point<T> get_p8() const { return *p8; }

private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4, p5, p6, p7, p8;
};

#endif