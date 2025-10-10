#include <iostream>
#include "Twelve.h"

// Лабораторная работа: Демонстрация класса Twelve для работы с двенадцатеричными числами
// Показывает различные конструкторы, включая перемещающий конструктор
// Демонстрирует Правило пяти (Rule of Five) для управления ресурсами

int main() {
    std::cout << "=== Лабораторная работа: Класс Twelve для двенадцатеричных чисел ===" << std::endl;
    
    // === ДЕМОНСТРАЦИЯ РАЗЛИЧНЫХ КОНСТРУКТОРОВ ===
    
    std::cout << "\n--- Создание объектов с помощью различных конструкторов ---" << std::endl;
    
    // Конструктор из строки (число A3B в 12-ричной системе)
    Twelve firstNumber("A3B");
    std::cout << "Первое число: ";
    firstNumber.print(std::cout) << std::endl;

    // Конструктор из списка инициализации (число 1A2 в 12-ричной системе)
    Twelve secondNumber{'1', 'A', '2'};
    std::cout << "Второе число: ";
    secondNumber.print(std::cout) << std::endl;

    // Конструктор с размером и значением по умолчанию
    Twelve thirdNumber(4, '5'); // Число 5555 в 12-ричной системе
    std::cout << "Третье число: ";
    thirdNumber.print(std::cout) << std::endl;

    // Конструктор по умолчанию (число 0)
    Twelve zeroNumber;
    std::cout << "Нулевое число: ";
    zeroNumber.print(std::cout) << std::endl;

    // === ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СЛОЖЕНИЯ ===
    
    std::cout << "\n--- Операции сложения ---" << std::endl;
    
    // Сложение чисел (создает новый объект)
    Twelve sumResult = firstNumber.add(secondNumber);
    std::cout << "A3B + 1A2 = ";
    sumResult.print(std::cout) << std::endl;

    // Сложение с нулем
    Twelve sumWithZero = firstNumber.add(zeroNumber);
    std::cout << "A3B + 0 = ";
    sumWithZero.print(std::cout) << std::endl;

    // === ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ ВЫЧИТАНИЯ ===
    
    std::cout << "\n--- Операции вычитания ---" << std::endl;
    
    try {
        // Успешное вычитание
        Twelve diffResult = firstNumber.remove(secondNumber);
        std::cout << "A3B - 1A2 = ";
        diffResult.print(std::cout) << std::endl;

        // Вычитание равных чисел
        Twelve sameNumber("123");
        Twelve zeroResult = sameNumber.remove(sameNumber);
        std::cout << "123 - 123 = ";
        zeroResult.print(std::cout) << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Ошибка при вычитании: " << e.what() << std::endl;
    }

    // === ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СРАВНЕНИЯ ===
    
    std::cout << "\n--- Операции сравнения ---" << std::endl;
    
    Twelve smallNumber("12");
    Twelve bigNumber("A3B");
    
    std::cout << "Число 12 равно числу A3B: " << (smallNumber.equals(bigNumber) ? "да" : "нет") << std::endl;
    std::cout << "Число 12 меньше числа A3B: " << (smallNumber.less(bigNumber) ? "да" : "нет") << std::endl;
    std::cout << "Число A3B больше числа 12: " << (bigNumber.greater(smallNumber) ? "да" : "нет") << std::endl;
    
    // Сравнение равных чисел
    Twelve anotherBigNumber("A3B");
    std::cout << "Число A3B равно числу A3B: " << (bigNumber.equals(anotherBigNumber) ? "да" : "нет") << std::endl;

    // === ДЕМОНСТРАЦИЯ ПЕРЕМЕЩАЮЩЕГО КОНСТРУКТОРА ===
    
    std::cout << "\n--- Перемещающий конструктор ---" << std::endl;
    
    // Создаем временный объект
    Twelve tempNumber("B45");
    std::cout << "Временное число до перемещения: ";
    tempNumber.print(std::cout) << std::endl;
    
    // Перемещающий конструктор - "крадет" ресурсы у tempNumber
    Twelve movedNumber(std::move(tempNumber));
    std::cout << "Перемещенное число: ";
    movedNumber.print(std::cout) << std::endl;
    
    // tempNumber теперь в неопределенном состоянии (но безопасном)

    // === ДЕМОНСТРАЦИЯ КОПИРУЮЩЕГО КОНСТРУКТОРА ===
    
    std::cout << "\n--- Копирующий конструктор ---" << std::endl;
    
    Twelve originalNumber("7A9");
    Twelve copiedNumber(originalNumber); // Копирующий конструктор
    
    std::cout << "Оригинальное число: ";
    originalNumber.print(std::cout) << std::endl;
    std::cout << "Скопированное число: ";
    copiedNumber.print(std::cout) << std::endl;

    // === ДЕМОНСТРАЦИЯ ОБРАБОТКИ ИСКЛЮЧЕНИЙ ===
    
    std::cout << "\n--- Обработка исключений ---" << std::endl;

    try {
        // Попытка создать число с недопустимыми цифрами
        Twelve invalidNumber("G12"); // G - недопустимая цифра в 12-ричной системе
        std::cout << "Это сообщение не должно выводиться" << std::endl;
        
    } catch (std::exception& e) {
        std::cerr << "Перехвачено исключение при создании: " << e.what() << std::endl;
    }

    try {
        // Попытка вычитания, которое приведет к отрицательному результату
        Twelve small("12");
        Twelve big("A3B");
        Twelve negativeResult = small.remove(big); // Должно вызвать исключение
        std::cout << "Это сообщение не должно выводиться" << std::endl;
        
    } catch (std::exception& e) {
        std::cerr << "Перехвачено исключение при вычитании: " << e.what() << std::endl;
    }

    try {
        // Попытка создать пустое число
        Twelve emptyNumber("");
        std::cout << "Это сообщение не должно выводиться" << std::endl;
        
    } catch (std::exception& e) {
        std::cerr << "Перехвачено исключение при создании пустого числа: " << e.what() << std::endl;
    }

    // === ДЕМОНСТРАЦИЯ КОМБИНИРОВАННЫХ ОПЕРАЦИЙ ===
    
    std::cout << "\n--- Комбинированные операции ---" << std::endl;
    
    Twelve num1("2A");
    Twelve num2("15");
    Twelve num3("7");
    
    // (num1 + num2) - num3
    Twelve combinedResult = num1.add(num2).remove(num3);
    std::cout << "(2A + 15) - 7 = ";
    combinedResult.print(std::cout) << std::endl;

    std::cout << "\n--- Выход из main() - вызов деструкторов ---" << std::endl;
    
    // Деструкторы вызываются в обратном порядке создания
    
    std::cout << "\n=== Лабораторная работа завершена ===" << std::endl;
    
    return 0;
}