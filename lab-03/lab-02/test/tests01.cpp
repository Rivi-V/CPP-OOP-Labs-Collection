#include <gtest/gtest.h>
#include "Twelve.h"

TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
    testing::internal::CaptureStdout();
    num.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "0");
}

TEST(TwelveTest, StringConstructor) {
    Twelve num("A3B");
    testing::internal::CaptureStdout();
    num.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "A3B");
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num{'1', 'A', '2'};
    testing::internal::CaptureStdout();
    num.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "2A1");  
}

TEST(TwelveTest, SizeValueConstructor) {
    Twelve num(4, '5');
    testing::internal::CaptureStdout();
    num.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "5555");
}

TEST(TwelveTest, BasicAddition) {
    Twelve num1("12");
    Twelve num2("15");
    Twelve result = num1.add(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "27");
}

TEST(TwelveTest, AdditionWithCarry) {
    Twelve num1("A");
    Twelve num2("3");
    Twelve result = num1.add(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "11");
}

TEST(TwelveTest, LargeAddition) {
    Twelve num1("A3B");
    Twelve num2("1A2");
    Twelve result = num1.add(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1021");
}

TEST(TwelveTest, AdditionWithZero) {
    Twelve num1("A3B");
    Twelve num2;
    Twelve result = num1.add(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "A3B");
}

TEST(TwelveTest, BasicSubtraction) {
    Twelve num1("27");
    Twelve num2("15");
    Twelve result = num1.remove(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "12");
}

TEST(TwelveTest, SubtractionWithBorrow) {
    Twelve num1("11");
    Twelve num2("3");
    Twelve result = num1.remove(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "A");
}

TEST(TwelveTest, SubtractionToZero) {
    Twelve num1("123");
    Twelve num2("123");
    Twelve result = num1.remove(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "0");
}

TEST(TwelveTest, EqualityTest) {
    Twelve num1("A3B");
    Twelve num2("A3B");
    ASSERT_TRUE(num1.equals(num2));
}

TEST(TwelveTest, InequalityTest) {
    Twelve num1("A3B");
    Twelve num2("123");
    ASSERT_FALSE(num1.equals(num2));
}

TEST(TwelveTest, LessThanTest) {
    Twelve num1("12");
    Twelve num2("A3B");
    ASSERT_TRUE(num1.less(num2));
}

TEST(TwelveTest, GreaterThanTest) {
    Twelve num1("A3B");
    Twelve num2("12");
    ASSERT_TRUE(num1.greater(num2));
}

TEST(TwelveTest, EqualNumbersNotLess) {
    Twelve num1("123");
    Twelve num2("123");
    ASSERT_FALSE(num1.less(num2));
}

TEST(TwelveTest, EqualNumbersNotGreater) {
    Twelve num1("123");
    Twelve num2("123");
    ASSERT_FALSE(num1.greater(num2));
}

TEST(TwelveTest, InvalidDigitException) {
    ASSERT_THROW(Twelve num("G12"), std::invalid_argument);
}

TEST(TwelveTest, EmptyStringException) {
    ASSERT_THROW(Twelve num(""), std::invalid_argument);
}

TEST(TwelveTest, NegativeResultException) {
    Twelve num1("12");
    Twelve num2("A3B");
    ASSERT_THROW(num1.remove(num2), std::invalid_argument);
}

TEST(TwelveTest, InvalidDigitInInitializerList) {
    ASSERT_THROW(Twelve num({'1', 'G', '2'}), std::invalid_argument);
}

TEST(TwelveTest, CopyConstructor) {
    Twelve original("A3B");
    Twelve copy(original);
    
    testing::internal::CaptureStdout();
    original.print(std::cout);
    std::string orig_output = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    copy.print(std::cout);
    std::string copy_output = testing::internal::GetCapturedStdout();
    
    ASSERT_EQ(orig_output, copy_output);
    ASSERT_TRUE(original.equals(copy));
}

TEST(TwelveTest, MoveConstructor) {
    Twelve original("A3B");
    Twelve moved(std::move(original));
    
    testing::internal::CaptureStdout();
    moved.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_EQ(output, "A3B");
}

TEST(TwelveTest, CombinedOperations) {
    Twelve num1("2A");
    Twelve num2("15");
    Twelve num3("7");
    
    Twelve result = num1.add(num2).remove(num3);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "38"); 
}

TEST(TwelveTest, ChainOfComparisons) {
    Twelve small("12");
    Twelve medium("5A");
    Twelve large("A3B");
    
    ASSERT_TRUE(small.less(medium));
    ASSERT_TRUE(medium.less(large));
    ASSERT_TRUE(small.less(large));
}

TEST(TwelveTest, SingleDigitNumbers) {
    Twelve num1("A");
    Twelve num2("B");
    Twelve result = num1.add(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "19");
}

TEST(TwelveTest, MaximumDigits) {
    Twelve num1("BB");
    Twelve num2("1");
    Twelve result = num1.add(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "100");
}

TEST(TwelveTest, ZeroSubtraction) {
    Twelve num1("A3B");
    Twelve num2;
    Twelve result = num1.remove(num2);
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "A3B");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}