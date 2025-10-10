#pragma once

#include <string>
#include <iostream>
#include <initializer_list>

class Twelve {
public:
    // Конструкторы
    Twelve();
    Twelve(const size_t &n, unsigned char t = 0);
    Twelve(const std::initializer_list<unsigned char> &t);
    Twelve(const std::string &t);
    
    // Копирование и перемещение
    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;
    
    // Операции с числами
    Twelve add(const Twelve& other) const;
    Twelve remove(const Twelve& other) const;
    bool equals(const Twelve& other) const;
    bool less(const Twelve& other) const;
    bool greater(const Twelve& other) const;
    
    // Вывод
    std::ostream& print(std::ostream& os) const;

    // Деструктор
    virtual ~Twelve() noexcept;

private:
    size_t _size;
    unsigned char* _data;
    
    // Вспомогательные методы
    bool isValidDigit(unsigned char c) const;
    unsigned char toDecimal(unsigned char c) const;
    unsigned char toTwelve(unsigned char n) const;
};