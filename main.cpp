#include "factory.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
    
    set_t array;
    
    // Генерируем NPC
    std::cout << "Generating 10 NPCs..." << std::endl;
    for (size_t i = 0; i < 10; ++i) {
        array.insert(factory(static_cast<NpcType>(std::rand() % 3 + 1),
                            std::rand() % 100,
                            std::rand() % 100));
    }
    
    std::cout << "\nInitial NPCs:" << std::endl;
    for (auto& npc : array) {
        npc->print();
    }
    
    // Сохраняем в файл
    save(array, "npc.txt");
    
    // Загружаем из файла
    set_t loaded = load("npc.txt");
    
    std::cout << "\nLoaded NPCs:" << std::endl;
    for (auto& npc : loaded) {
        npc->print();
    }
    
    // Проводим бои с разной дистанцией
    std::cout << "\n=== STARTING BATTLES ===" << std::endl;
    
    for (size_t distance = 20; distance <= 100 && !loaded.empty(); distance += 20) {
        auto dead_list = fight(loaded, distance);
        
        std::cout << "\nDistance: " << distance << std::endl;
        std::cout << "Killed: " << dead_list.size() << std::endl;
        
        // Удаляем мертвых
        for (auto& dead : dead_list) {
            loaded.erase(dead);
        }
        
        std::cout << "Survivors: " << loaded.size() << std::endl;
    }
    
    std::cout << "\n=== FINAL SURVIVORS ===" << std::endl;
    for (auto& npc : loaded) {
        npc->print();
    }
    
    return 0;
}