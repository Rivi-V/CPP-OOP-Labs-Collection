#include <iostream>
#include <memory>
#include "array.h"
#include "figure.h"
#include "point.h"
#include "square.h"
#include "triangle.h"
#include "octagon.h"

int main() {
    std::cout << "=== Лабораторная работа 3 ===" << std::endl;

    std::cout << "\n1. Демонстрация Array<std::shared_ptr<Figure<double>>>:" << std::endl;
    Array<std::shared_ptr<Figure<double>>> figures;
    
    std::cout << "\n2. Создаем фигуры:" << std::endl;
    
    auto square = std::make_shared<Square<double>>(
        Point<double>(0, 0), Point<double>(2, 0),
        Point<double>(2, 2), Point<double>(0, 2)
    );
    figures.push_back(square);
    std::cout << "   - Квадрат создан" << std::endl;
    
    auto triangle = std::make_shared<Triangle<double>>(
        Point<double>(0, 0), Point<double>(3, 0), Point<double>(1.5, 2.6)
    );
    figures.push_back(triangle);
    std::cout << "   - Треугольник создан" << std::endl;
    
    auto octagon = std::make_shared<Octagon<double>>(
        Point<double>(1, 0), Point<double>(0.7, 0.7), Point<double>(0, 1),
        Point<double>(-0.7, 0.7), Point<double>(-1, 0), 
        Point<double>(-0.7, -0.7), Point<double>(0, -1), Point<double>(0.7, -0.7)
    );
    figures.push_back(octagon);
    std::cout << "   - Восьмиугольник создан" << std::endl;
    
    std::cout << "\n3. Информация о фигурах:" << std::endl;
    for (size_t i = 0; i < figures.getSize(); i++) {
        std::cout << "Фигура " << (i + 1) << ": " << *figures[i] << std::endl;
        Point<double> center = figures[i]->geometricCenter();
        std::cout << "Центр: (" << center.get_X() << ", " << center.get_Y() << ")" << std::endl;
        std::cout << "Площадь: " << static_cast<double>(*figures[i]) << std::endl << std::endl;
    }
    
    std::cout << "4. Общая площадь всех фигур: ";
    double totalArea = 0;
    for (size_t i = 0; i < figures.getSize(); i++) {
        totalArea += static_cast<double>(*figures[i]);
    }
    std::cout << totalArea << std::endl;
    
    std::cout << "\n5. Удаляем фигуру по индексу 1:" << std::endl;
    figures.erase(1);
    std::cout << "Осталось фигур: " << figures.getSize() << std::endl;
    
    std::cout << "\n6. Оставшиеся фигуры:" << std::endl;
    for (size_t i = 0; i < figures.getSize(); i++) {
        std::cout << "Фигура " << (i + 1) << ": " << *figures[i] << std::endl;
        std::cout << "Площадь: " << static_cast<double>(*figures[i]) << std::endl;
    }
    
    std::cout << "\n7. Демонстрация Array<Square<int>>:" << std::endl;
    Array<Square<int>> squaresArray;
    
    squaresArray.push_back(Square<int>(
        Point<int>(0, 0), Point<int>(5, 0),
        Point<int>(5, 5), Point<int>(0, 5)
    ));
    
    squaresArray.push_back(Square<int>(
        Point<int>(1, 1), Point<int>(6, 1),
        Point<int>(6, 6), Point<int>(1, 6)
    ));
    
    std::cout << "Квадраты в массиве:" << std::endl;
    for (size_t i = 0; i < squaresArray.getSize(); i++) {
        std::cout << "Квадрат " << (i + 1) << ": " << squaresArray[i] << std::endl;
        std::cout << "Площадь: " << static_cast<double>(squaresArray[i]) << std::endl;
    }
    
    std::cout << "\n=== Завершено ===" << std::endl;
    
    return 0;
}