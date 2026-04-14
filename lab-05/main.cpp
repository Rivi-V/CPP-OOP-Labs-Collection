#include <iostream>
#include <string>
#include "fixed_block_memory_resource.h"
#include "queue.h"

struct Car {
    std::string brand;
    std::string model;
    int year;
    double price;

    Car(const std::string& b, const std::string& m, int y, double p) 
        : brand(b), model(m), year(y), price(p) {}
    
    Car() : year(0), price(0.0) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << "Car{brand: " << car.brand 
           << ", model: " << car.model 
           << ", year: " << car.year 
           << ", price: $" << car.price << "}";
        return os;
    }
};

int main() {
    // memory_resource с фиксированным блоком 1MB
    FixedBlockMemoryResource memory_resource(1024 * 1024);
    
    // аллокатор, использующий memory_resource
    std::pmr::polymorphic_allocator<int> allocator(&memory_resource);

    // Демонстрация с простыми типами (int)
    std::cout << "=== int ===" << std::endl;
    Queue<int, std::pmr::polymorphic_allocator<int>> int_queue(allocator);
    
    for (int i = 1; i <= 5; ++i) {
        int_queue.push(i * 10);
        std::cout << "Push: " << i * 10 << std::endl;
    }
    
    std::cout << "Queue contents: ";
    for (auto it = int_queue.begin(); it != int_queue.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    while (!int_queue.empty()) {
        std::cout << "Pop: " << int_queue.front() << std::endl;
        int_queue.pop();
    }

    // Демонстрация со сложными типами (Car)
    std::cout << "\n=== Car ===" << std::endl;
    Queue<Car, std::pmr::polymorphic_allocator<Car>> car_queue(allocator);
    
    car_queue.emplace("Toyota", "Camry", 2022, 25000.0);
    car_queue.emplace("Honda", "Civic", 2021, 22000.0);
    car_queue.emplace("Ford", "Mustang", 2023, 35000.0);
    car_queue.emplace("Tesla", "Model 3", 2023, 45000.0);
    
    std::cout << "Car queue contents:" << std::endl;
    for (const auto& car : car_queue) {
        std::cout << "  " << car << std::endl;
    }
    
    // Демонстрация pop
    std::cout << "\nProcessing cars from queue:" << std::endl;
    while (!car_queue.empty()) {
        std::cout << "Processing: " << car_queue.front() << std::endl;
        car_queue.pop();
    }

    return 0;
}