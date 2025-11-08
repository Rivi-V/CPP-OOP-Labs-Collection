#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include "figure.h"
#include "point.h"
#include "square.h"
#include "triangle.h"
#include "octagon.h"
#include "array.h"

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    ASSERT_DOUBLE_EQ(p.get_X(), 0.0);
    ASSERT_DOUBLE_EQ(p.get_Y(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 2.7);
    ASSERT_DOUBLE_EQ(p.get_X(), 3.5);
    ASSERT_DOUBLE_EQ(p.get_Y(), 2.7);
}

TEST(PointTest, SettersAndGetters) {
    Point<double> p;
    p.set_X(1.1);
    p.set_Y(2.2);
    ASSERT_DOUBLE_EQ(p.get_X(), 1.1);
    ASSERT_DOUBLE_EQ(p.get_Y(), 2.2);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(3.0, 4.0);
    
    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 == p3);
}

TEST(PointTest, DifferentTypes) {
    Point<int> int_point(1, 2);
    Point<float> float_point(1.5f, 2.5f);
    
    ASSERT_EQ(int_point.get_X(), 1);
    ASSERT_EQ(int_point.get_Y(), 2);
    ASSERT_FLOAT_EQ(float_point.get_X(), 1.5f);
    ASSERT_FLOAT_EQ(float_point.get_Y(), 2.5f);
}

TEST(SquareTest, GeometricCenter) {
    Point<double> p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Square<double> s(p1, p2, p3, p4);
    
    Point<double> center = s.geometricCenter();
    ASSERT_DOUBLE_EQ(center.get_X(), 1.0);
    ASSERT_DOUBLE_EQ(center.get_Y(), 1.0);
}

TEST(SquareTest, AreaCalculation) {
    Point<double> p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Square<double> s(p1, p2, p3, p4);
    
    double area = static_cast<double>(s);
    ASSERT_NEAR(area, 4.0, 0.001);
}

TEST(SquareTest, OutputOperator) {
    Point<double> p1(0, 0), p2(1, 0), p3(1, 1), p4(0, 1);
    Square<double> s(p1, p2, p3, p4);
    
    std::stringstream ss;
    ss << s;
    
    ASSERT_EQ(ss.str(), "Square: 0 0 1 0 1 1 0 1");
}

TEST(TriangleTest, GeometricCenter) {
    Point<double> p1(0, 0), p2(3, 0), p3(1.5, 2.6);
    Triangle<double> t(p1, p2, p3);
    
    Point<double> center = t.geometricCenter();
    ASSERT_DOUBLE_EQ(center.get_X(), 1.5);
    ASSERT_NEAR(center.get_Y(), 0.866, 0.001);
}

TEST(TriangleTest, AreaCalculation) {
    Point<double> p1(0, 0), p2(3, 0), p3(1.5, 2.6);
    Triangle<double> t(p1, p2, p3);
    
    double area = static_cast<double>(t);
    ASSERT_NEAR(area, 3.9, 0.1);
}

TEST(TriangleTest, OutputOperator) {
    Point<double> p1(1, 2), p2(3, 4), p3(5, 6);
    Triangle<double> t(p1, p2, p3);
    
    std::stringstream ss;
    ss << t;
    
    ASSERT_EQ(ss.str(), "Triangle: 1 2 3 4 5 6");
}

TEST(OctagonTest, GeometricCenter) {
    Point<double> p1(1, 0), p2(0.7, 0.7), p3(0, 1), p4(-0.7, 0.7),
                 p5(-1, 0), p6(-0.7, -0.7), p7(0, -1), p8(0.7, -0.7);
    Octagon<double> o(p1, p2, p3, p4, p5, p6, p7, p8);
    
    Point<double> center = o.geometricCenter();
    ASSERT_NEAR(center.get_X(), 0.0, 0.001);
    ASSERT_NEAR(center.get_Y(), 0.0, 0.001);
}

TEST(OctagonTest, AreaCalculation) {
    Point<double> p1(1, 0), p2(0.7, 0.7), p3(0, 1), p4(-0.7, 0.7),
                 p5(-1, 0), p6(-0.7, -0.7), p7(0, -1), p8(0.7, -0.7);
    Octagon<double> o(p1, p2, p3, p4, p5, p6, p7, p8);
    
    double area = static_cast<double>(o);
    ASSERT_GT(area, 0.0);
}

TEST(OctagonTest, OutputOperator) {
    Point<double> p1(1, 1), p2(2, 2), p3(3, 3), p4(4, 4),
                 p5(5, 5), p6(6, 6), p7(7, 7), p8(8, 8);
    Octagon<double> o(p1, p2, p3, p4, p5, p6, p7, p8);
    
    std::stringstream ss;
    ss << o;
    
    ASSERT_EQ(ss.str(), "Octagon: 1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8");
}

TEST(PolymorphismTest, FigurePointer) {
    Point<double> p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    std::shared_ptr<Figure<double>> figure = std::make_shared<Square<double>>(p1, p2, p3, p4);
    
    Point<double> center = figure->geometricCenter();
    double area = static_cast<double>(*figure);
    
    ASSERT_DOUBLE_EQ(center.get_X(), 1.0);
    ASSERT_NEAR(area, 4.0, 0.001);
}

TEST(PolymorphismTest, ArrayOfFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    Point<double> s1(0, 0), s2(2, 0), s3(2, 2), s4(0, 2);
    figures.push_back(std::make_shared<Square<double>>(s1, s2, s3, s4));
    
    Point<double> t1(0, 0), t2(3, 0), t3(1.5, 2.6);
    figures.push_back(std::make_shared<Triangle<double>>(t1, t2, t3));
    
    double totalArea = 0;
    for (size_t i = 0; i < figures.getSize(); i++) {
        totalArea += static_cast<double>(*figures[i]);
    }
    
    ASSERT_GT(totalArea, 0.0);
}

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    ASSERT_EQ(arr.getSize(), 0);
    ASSERT_GE(arr.getCapacity(), 0);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    
    ASSERT_EQ(arr.getSize(), 2);
    ASSERT_EQ(arr[0], 1);
    ASSERT_EQ(arr[1], 2);
}

TEST(ArrayTest, Erase) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.erase(1);
    
    ASSERT_EQ(arr.getSize(), 2);
    ASSERT_EQ(arr[0], 1);
    ASSERT_EQ(arr[1], 3);
}

TEST(ArrayTest, MoveSemantics) {
    Array<std::string> arr;
    std::string str = "test";
    arr.push_back(std::move(str));
    
    ASSERT_TRUE(str.empty());
    ASSERT_EQ(arr[0], "test");
}

TEST(ArrayTest, DifferentTypes) {
    Array<Square<int>> squares;
    squares.push_back(Square<int>(
        Point<int>(0, 0), Point<int>(1, 0),
        Point<int>(1, 1), Point<int>(0, 1)
    ));
    
    ASSERT_EQ(squares.getSize(), 1);
    ASSERT_NEAR(static_cast<double>(squares[0]), 1.0, 0.001);
}

TEST(AssignmentTest, CopyAssignment) {
    Point<double> p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Square<double> s1(p1, p2, p3, p4);
    Square<double> s2;
    
    s2 = s1;
    
    ASSERT_TRUE(s1 == s2);
}

TEST(AssignmentTest, MoveAssignment) {
    Point<double> p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Square<double> s1(p1, p2, p3, p4);
    Square<double> s2;
    
    s2 = std::move(s1);
    
    ASSERT_DOUBLE_EQ(s2.get_p1().get_X(), 0.0);
}

TEST(TotalAreaTest, MultipleFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    Point<double> s1(0, 0), s2(2, 0), s3(2, 2), s4(0, 2);
    figures.push_back(std::make_shared<Square<double>>(s1, s2, s3, s4));
    
    Point<double> t1(0, 0), t2(3, 0), t3(1.5, 2.6);
    figures.push_back(std::make_shared<Triangle<double>>(t1, t2, t3));
    
    Point<double> o1(1, 0), o2(0.7, 0.7), o3(0, 1), o4(-0.7, 0.7),
                 o5(-1, 0), o6(-0.7, -0.7), o7(0, -1), o8(0.7, -0.7);
    figures.push_back(std::make_shared<Octagon<double>>(o1, o2, o3, o4, o5, o6, o7, o8));
    
    double total = 0;
    for (size_t i = 0; i < figures.getSize(); i++) {
        total += static_cast<double>(*figures[i]);
    }
    
    ASSERT_GT(total, 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}