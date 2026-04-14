#include <iostream>
#include <vector>
#include <sstream>
#include "figure.h"
#include "trapeze.h"
#include "rhombus.h"
#include "pentagon.h"

int main() {
    std::cout << "=== Лабораторная работа 3 ===" << std::endl;
    
    std::vector<Figure*> figures;
    
    std::cout << "\n1. Создаем фигуры вручную:" << std::endl;
    
    Point t1(0, 0), t2(4, 0), t3(3, 3), t4(1, 3);
    figures.push_back(new Trapeze(t1, t2, t3, t4));
    std::cout << "   - Трапеция создана" << std::endl;
    
    std::cout << "\n2. Демонстрация ввода фигуры (operator>>):" << std::endl;
    
    Rhombus* rh = new Rhombus();
    std::stringstream test_input("1 2 3 4 5 6 7 8");
    test_input >> *rh;
    figures.push_back(rh);
    std::cout << "   Тестовый ввод: " << *rh << std::endl;
    
    std::cout << "\n3. Еще одна фигура (пятиугольник):" << std::endl;
    Point p1(0, 0), p2(2, 1), p3(3, 3), p4(1, 4), p5(-1, 2);
    figures.push_back(new Pentagon(p1, p2, p3, p4, p5));
    std::cout << "   - Пятиугольник создан" << std::endl;
    
    std::cout << "\n4. Информация о всех фигурах (operator<<):" << std::endl;
    
    for (int i = 0; i < figures.size(); i++) {
        std::cout << "   Фигура " << (i + 1) << ": " << *figures[i] << std::endl;
        
        Point center = figures[i]->geometricCenter();
        std::cout << "   Центр: (" << center.get_X() << ", " << center.get_Y() << ")" << std::endl;
        
        double area = (double)*figures[i];
        std::cout << "   Площадь: " << area << std::endl << std::endl;
    }
    
    std::cout << "5. Общая площадь: ";
    double total = 0;
    for (int i = 0; i < figures.size(); i++) {
        total += (double)*figures[i];
    }
    std::cout << total << std::endl;
    
    std::cout << "\n6. Удаляем фигуру по индексу 0:" << std::endl;
    if (!figures.empty()) {
        delete figures[0];
        figures.erase(figures.begin());
        std::cout << "   Удалено. Осталось фигур: " << figures.size() << std::endl;
    }
    
    std::cout << "\n7. Сравнение фигур (operator==):" << std::endl;
    if (figures.size() >= 2) {
        if (*figures[0] == *figures[1]) {
            std::cout << "   Фигуры одинаковые" << std::endl;
        } else {
            std::cout << "   Фигуры разные" << std::endl;
        }
    }
    
    for (Figure* fig : figures) {
        delete fig;
    }
    
    std::cout << "\n=== Демонстрация завершена ===" << std::endl;
    
    return 0;
}