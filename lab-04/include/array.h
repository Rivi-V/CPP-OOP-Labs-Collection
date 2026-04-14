#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <algorithm>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t capacity;
    size_t size;
    
    void resize(size_t new_capacity) {
        std::shared_ptr<T[]> new_data(new T[new_capacity]);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = new_data;
        capacity = new_capacity;
    }
    
public:
    Array() : capacity(10), size(0) {
        data = std::shared_ptr<T[]>(new T[capacity]);
    }
    
    Array(size_t initial_capacity) : capacity(initial_capacity), size(0) {
        data = std::shared_ptr<T[]>(new T[capacity]);
    }
    
    void push_back(const T& item) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size] = item;
        ++size;
    }
    
    void push_back(T&& item) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size] = std::move(item);
        ++size;
    }
    
    void erase(size_t index) {
        if (index >= size) return;
        
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    size_t getSize() const {
        return size;
    }
    
    size_t getCapacity() const {
        return capacity;
    }
};

#endif