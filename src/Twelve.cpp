#include "Twelve.h"
#include <stdexcept>
#include <algorithm>

bool Twelve::isValidDigit(unsigned char c) const {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'B') || (c >= 'a' && c <= 'b');
}

unsigned char Twelve::toDecimal(unsigned char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'B') return c - 'A' + 10;
    if (c >= 'a' && c <= 'b') return c - 'a' + 10;
    throw std::invalid_argument("Invalid digit");
}

unsigned char Twelve::toTwelve(unsigned char n) const {
    if (n < 10) return '0' + n;
    if (n < 12) return 'A' + (n - 10);
    throw std::invalid_argument("Invalid number");
}


Twelve::Twelve() : _size(1), _data(new unsigned char[1]) {
    _data[0] = '0';
}

Twelve::Twelve(const size_t &n, unsigned char t) : _size(n), _data(new unsigned char[n]) {
    if (n == 0) throw std::invalid_argument("Size can't be zero");
    if (!isValidDigit(t)) throw std::invalid_argument("Invalid digit");
    
    for (size_t i = 0; i < n; ++i) {
        _data[i] = t;
    }
}

Twelve::Twelve(const std::initializer_list<unsigned char> &t) : 
    _size(t.size()), 
    _data(new unsigned char[t.size()]) 
{
    if (_size == 0) throw std::invalid_argument("Size can't be zero");
    
    size_t i = 0;
    for (auto it = t.begin(); it != t.end(); ++it, ++i) {
        if (!isValidDigit(*it)) throw std::invalid_argument("Invalid digit");
        _data[i] = *it;
    }
}


Twelve::Twelve(const std::string &t) : _size(t.size()), _data(new unsigned char[t.size()]) {
    if (_size == 0) throw std::invalid_argument("Size can't be zero");
    
    for (size_t i = 0; i < _size; ++i) {
        if (!isValidDigit(t[i])) throw std::invalid_argument("Invalid digit");
        _data[i] = t[_size - 1 - i]; 
    }
}

Twelve::Twelve(const Twelve& other) : 
    _size(other._size), 
    _data(new unsigned char[other._size]) 
{
    std::copy(other._data, other._data + _size, _data);
}

Twelve::Twelve(Twelve&& other) noexcept : 
    _size(other._size), 
    _data(other._data) 
{
    other._size = 0;
    other._data = nullptr;
}

Twelve Twelve::add(const Twelve& other) const {
    size_t maxSize = std::max(_size, other._size);
    std::string result;
    int carry = 0;

    for (size_t i = 0; i < maxSize || carry; ++i) {
        int sum = carry;
        if (i < _size) sum += toDecimal(_data[i]);
        if (i < other._size) sum += toDecimal(other._data[i]);
        
        carry = sum / 12;
        result.push_back(toTwelve(sum % 12));
    }

    std::reverse(result.begin(), result.end());
    return Twelve(result);
}

Twelve Twelve::remove(const Twelve& other) const {
    if (this->less(other)) throw std::invalid_argument("Result would be negative");
    
    std::string result;
    int borrow = 0;

    for (size_t i = 0; i < _size; ++i) {
        int top = toDecimal(_data[i]);
        int bottom = (i < other._size) ? toDecimal(other._data[i]) : 0;
        
        if (borrow) {
            top -= 1;
            borrow = 0;
        }
        
        if (top < bottom) {
            top += 12;
            borrow = 1;
        }
        
        result.push_back(toTwelve(top - bottom));
    }

    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    
    std::reverse(result.begin(), result.end());
    return Twelve(result);
}

bool Twelve::equals(const Twelve& other) const {
    if (_size != other._size) return false;
    
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] != other._data[i]) return false;
    }
    return true;
}

bool Twelve::less(const Twelve& other) const {
    if (_size != other._size) return _size < other._size;
    
    for (int i = _size - 1; i >= 0; --i) {
        if (_data[i] != other._data[i]) 
            return toDecimal(_data[i]) < toDecimal(other._data[i]);
    }
    return false;
}

bool Twelve::greater(const Twelve& other) const {
    return !this->less(other) && !this->equals(other);
}


std::ostream& Twelve::print(std::ostream& os) const {
    for (int i = _size - 1; i >= 0; --i) {
        os << _data[i];
    }
    return os;
}

Twelve::~Twelve() noexcept {
    delete[] _data;
}