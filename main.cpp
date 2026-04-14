#include <iostream>
#include "Twelve.h"

int main() {
    std::cout << "=== Лабораторная работа: Класс Twelve для двенадцатеричных чисел ===" << std::endl;
    
    std::cout << "\n--- Создание объектов с помощью различных конструкторов ---" << std::endl;
    
    Twelve f("A3B");
    std::cout << "Первое число: ";
    f.print(std::cout) << std::endl;

    Twelve s{'1', 'A', '2'};
    std::cout << "Второе число: ";
    s.print(std::cout) << std::endl;

    Twelve t(4, '5');
    std::cout << "Третье число: ";
    t.print(std::cout) << std::endl;

    Twelve z;
    std::cout << "Нулевое число: ";
    z.print(std::cout) << std::endl;
    
    std::cout << "\n--- Операции сложения ---" << std::endl;
    
    Twelve sum = f.add(s);
    std::cout << "A3B + 1A2 = ";
    sum.print(std::cout) << std::endl;

    Twelve zerosum = f.add(z);
    std::cout << "A3B + 0 = ";
    zerosum.print(std::cout) << std::endl;
    
    std::cout << "\n--- Операции вычитания ---" << std::endl;
    
    try {
        Twelve diff = f.remove(s);
        std::cout << "A3B - 1A2 = ";
        diff.print(std::cout) << std::endl;

        Twelve same("123");
        Twelve zero_res = same.remove(same);
        std::cout << "123 - 123 = ";
        zero_res.print(std::cout) << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Ошибка при вычитании: " << e.what() << std::endl;
    }
    

    std::cout << "\n--- Операции сравнения ---" << std::endl;
    
    Twelve small("12");
    Twelve bigg("A3B");
    
    std::cout << "Число 12 равно числу A3B: " << (small.equals(bigg) ? "да" : "нет") << std::endl;
    std::cout << "Число 12 меньше числа A3B: " << (small.less(bigg) ? "да" : "нет") << std::endl;
    std::cout << "Число A3B больше числа 12: " << (bigg.greater(small) ? "да" : "нет") << std::endl;
    
    Twelve big_two("A3B");
    std::cout << "Число A3B равно числу A3B: " << (bigg.equals(big_two) ? "да" : "нет") << std::endl;

    
    std::cout << "\n--- Перемещающий конструктор ---" << std::endl;
    
    Twelve temp("B45");
    std::cout << "Временное число до перемещения: ";
    temp.print(std::cout) << std::endl;
    
    Twelve moved(std::move(temp));
    std::cout << "Перемещенное число: ";
    moved.print(std::cout) << std::endl;


    
    std::cout << "\n--- Копирующий конструктор ---" << std::endl;
    
    Twelve original("7A9");
    Twelve copied(original); 
    
    std::cout << "Оригинальное число: ";
    original.print(std::cout) << std::endl;
    std::cout << "Скопированное число: ";
    copied.print(std::cout) << std::endl;

    
    std::cout << "\n--- Обработка исключений ---" << std::endl;

    try {
        Twelve invalid("G12");
        std::cout << "Это сообщение не должно выводиться" << std::endl;
        
    } catch (std::exception& e) {
        std::cerr << "Перехвачено исключение при создании: " << e.what() << std::endl;
    }

    try {
        Twelve small("12");
        Twelve big("A3B");
        Twelve neg_res = small.remove(big); 
        std::cout << "Это сообщение не должно выводиться" << std::endl;
        
    } catch (std::exception& e) {
        std::cerr << "Перехвачено исключение при вычитании: " << e.what() << std::endl;
    }

    try {
        Twelve empty("");
        std::cout << "Это сообщение не должно выводиться" << std::endl;
        
    } catch (std::exception& e) {
        std::cerr << "Перехвачено исключение при создании пустого числа: " << e.what() << std::endl;
    }

    
    std::cout << "\n--- Комбинированные операции ---" << std::endl;
    
    Twelve num1("2A");
    Twelve num2("15");
    Twelve num3("7");
    
    Twelve comb = num1.add(num2).remove(num3);
    std::cout << "(2A + 15) - 7 = ";
    comb.print(std::cout) << std::endl;

    std::cout << "\n--- Выход из main() - вызов деструкторов ---" << std::endl;
    
    std::cout << "\n=== Лабораторная работа завершена ===" << std::endl;
    
    return 0;
}