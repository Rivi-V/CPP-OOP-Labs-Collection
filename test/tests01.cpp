#include <gtest/gtest.h>
#include <sstream>
#include "figure.h"
#include "trapeze.h"
#include "rhombus.h"
#include "pentagon.h"

TEST(PointTest, DefaultConstructor) {
    Point p;
    ASSERT_DOUBLE_EQ(p.get_X(), 0.0);
    ASSERT_DOUBLE_EQ(p.get_Y(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3.5, 2.7);
    ASSERT_DOUBLE_EQ(p.get_X(), 3.5);
    ASSERT_DOUBLE_EQ(p.get_Y(), 2.7);
}

TEST(PointTest, SettersAndGetters) {
    Point p;
    p.set_X(1.1);
    p.set_Y(2.2);
    ASSERT_DOUBLE_EQ(p.get_X(), 1.1);
    ASSERT_DOUBLE_EQ(p.get_Y(), 2.2);
}

TEST(PointTest, EqualityOperator) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(3.0, 4.0);
    
    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 == p3);
}


TEST(TrapezeTest, DefaultConstructor) {
    Trapeze t;
    ASSERT_DOUBLE_EQ(t.get_p1().get_X(), 0.0);
    ASSERT_DOUBLE_EQ(t.get_p1().get_Y(), 0.0);
}

TEST(TrapezeTest, ParameterizedConstructor) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Trapeze t(p1, p2, p3, p4);
    
    ASSERT_TRUE(t.get_p1() == p1);
    ASSERT_TRUE(t.get_p2() == p2);
}

TEST(TrapezeTest, GeometricCenter) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Trapeze t(p1, p2, p3, p4);
    
    Point center = t.geometricCenter();
    ASSERT_DOUBLE_EQ(center.get_X(), 2.0);
    ASSERT_DOUBLE_EQ(center.get_Y(), 1.5);
}

TEST(TrapezeTest, AreaCalculation) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Trapeze t(p1, p2, p3, p4);
    
    double area = (double)t;
    ASSERT_NEAR(area, 9.0, 0.001);
}

TEST(TrapezeTest, OutputOperator) {
    Point p1(1, 2), p2(3, 4), p3(5, 6), p4(7, 8);
    Trapeze t(p1, p2, p3, p4);
    
    std::stringstream ss;
    ss << t;
    
    ASSERT_EQ(ss.str(), "Trapeze: 1 2 3 4 5 6 7 8");
}

TEST(TrapezeTest, InputOperator) {
    Trapeze t;
    std::stringstream ss("1 2 3 4 5 6 7 8");
    ss >> t;
    
    ASSERT_DOUBLE_EQ(t.get_p1().get_X(), 1.0);
    ASSERT_DOUBLE_EQ(t.get_p1().get_Y(), 2.0);
    ASSERT_DOUBLE_EQ(t.get_p4().get_X(), 7.0);
    ASSERT_DOUBLE_EQ(t.get_p4().get_Y(), 8.0);
}

TEST(TrapezeTest, EqualityOperator) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Trapeze t1(p1, p2, p3, p4);
    Trapeze t2(p1, p2, p3, p4);
    Trapeze t3(p4, p3, p2, p1); 
    
    ASSERT_TRUE(t1 == t2);
    ASSERT_FALSE(t1 == t3);
}

TEST(RhombusTest, GeometricCenter) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r(p1, p2, p3, p4);
    
    Point center = r.geometricCenter();
    ASSERT_DOUBLE_EQ(center.get_X(), 2.0);
    ASSERT_DOUBLE_EQ(center.get_Y(), 0.0);
}

TEST(RhombusTest, AreaCalculation) {
    Point p1(0, 0), p2(2, 3), p3(4, 0), p4(2, -3);
    Rhombus r(p1, p2, p3, p4);
    
    double area = (double)r;
    ASSERT_NEAR(area, 12.0, 0.001);
}

TEST(RhombusTest, OutputOperator) {
    Point p1(1, 1), p2(2, 2), p3(3, 3), p4(4, 4);
    Rhombus r(p1, p2, p3, p4);
    
    std::stringstream ss;
    ss << r;
    
    ASSERT_EQ(ss.str(), "Rhombus: 1 1 2 2 3 3 4 4");
}

TEST(PentagonTest, GeometricCenter) {
    Point p1(0, 0), p2(2, 1), p3(3, 3), p4(1, 4), p5(-1, 2);
    Pentagon p(p1, p2, p3, p4, p5);
    
    Point center = p.geometricCenter();
    ASSERT_DOUBLE_EQ(center.get_X(), 1.0);
    ASSERT_DOUBLE_EQ(center.get_Y(), 2.0);
}

TEST(PentagonTest, AreaCalculation) {
    Point p1(0, 0), p2(1, 0), p3(1.5, 0.866), p4(0.5, 0.866), p5(-0.5, 0.866);
    Pentagon p(p1, p2, p3, p4, p5);
    
    double area = (double)p;
    ASSERT_GT(area, 0.0);
}

TEST(PentagonTest, OutputOperator) {
    Point p1(1, 1), p2(2, 2), p3(3, 3), p4(4, 4), p5(5, 5);
    Pentagon p(p1, p2, p3, p4, p5);
    
    std::stringstream ss;
    ss << p;
    
    ASSERT_EQ(ss.str(), "Pentagon: 1 1 2 2 3 3 4 4 5 5");
}

TEST(PolymorphismTest, FigurePointer) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Figure* figure = new Trapeze(p1, p2, p3, p4);
    
    Point center = figure->geometricCenter();
    double area = (double)*figure;
    
    ASSERT_DOUBLE_EQ(center.get_X(), 2.0);
    ASSERT_NEAR(area, 9.0, 0.001);
    
    delete figure;
}

TEST(PolymorphismTest, VectorOfFigures) {
    std::vector<Figure*> figures;
    
    Point t1(0, 0), t2(4, 0), t3(3, 3), t4(1, 3);
    figures.push_back(new Trapeze(t1, t2, t3, t4));
    
    Point r1(0, 0), r2(2, 3), r3(4, 0), r4(2, -3);
    figures.push_back(new Rhombus(r1, r2, r3, r4));
    
    double totalArea = 0;
    for (Figure* fig : figures) {
        totalArea += (double)*fig;
    }
    
    ASSERT_GT(totalArea, 0.0);
    
    for (Figure* fig : figures) {
        delete fig;
    }
}

TEST(AssignmentTest, CopyAssignment) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Trapeze t1(p1, p2, p3, p4);
    Trapeze t2;
    
    t2 = t1;
    
    ASSERT_TRUE(t1 == t2);
}

TEST(AssignmentTest, MoveAssignment) {
    Point p1(0, 0), p2(4, 0), p3(3, 3), p4(1, 3);
    Trapeze t1(p1, p2, p3, p4);
    Trapeze t2;
    
    t2 = std::move(t1);
    
    ASSERT_DOUBLE_EQ(t2.get_p1().get_X(), 0.0);
}

TEST(TotalAreaTest, MultipleFigures) {
    std::vector<Figure*> figures;
    
    Point t1(0, 0), t2(4, 0), t3(3, 3), t4(1, 3);
    figures.push_back(new Trapeze(t1, t2, t3, t4)); 
    
    Point r1(0, 0), r2(2, 3), r3(4, 0), r4(2, -3);
    figures.push_back(new Rhombus(r1, r2, r3, r4)); 
    
    double total = 0;
    for (Figure* fig : figures) {
        total += (double)*fig;
    }
    
    ASSERT_NEAR(total, 21.0, 0.1);
    
    for (Figure* fig : figures) {
        delete fig;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}