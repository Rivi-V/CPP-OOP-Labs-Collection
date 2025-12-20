#include "map_printer.h"
#include <iostream>
#include <algorithm>
#include "common.h" 

void MapPrinter::print_map(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    
    // Матрица для подсчета NPC в каждой клетке
    std::vector<std::vector<int>> dragon_counts(DISPLAY_WIDTH, 
                                                std::vector<int>(DISPLAY_HEIGHT, 0));
    std::vector<std::vector<int>> elf_counts(DISPLAY_WIDTH, 
                                             std::vector<int>(DISPLAY_HEIGHT, 0));
    std::vector<std::vector<int>> knight_counts(DISPLAY_WIDTH, 
                                                std::vector<int>(DISPLAY_HEIGHT, 0));
    
    // Подсчет NPC в клетках
    for (const auto& npc : npcs) {
        if (!npc->is_alive()) continue;
        
        int x = npc->get_x();
        int y = npc->get_y();
        int cell_x = x / CELL_SIZE;
        int cell_y = y / CELL_SIZE;
        
        if (cell_x >= 0 && cell_x < DISPLAY_WIDTH && 
            cell_y >= 0 && cell_y < DISPLAY_HEIGHT) {
            switch (npc->get_type()) {
                case NpcType::DragonType:
                    dragon_counts[cell_x][cell_y]++;
                    break;
                case NpcType::ElfType:
                    elf_counts[cell_x][cell_y]++;
                    break;
                case NpcType::KnightType:
                    knight_counts[cell_x][cell_y]++;
                    break;
            }
        }
    }
    
    // Очистка экрана (для Linux/Mac)
    // std::cout << "\033[2J\033[1;1H";
    std::cout << "\n=== Карта мира (" << DISPLAY_WIDTH << "x" << DISPLAY_HEIGHT 
              << " клеток, каждая " << CELL_SIZE << "x" << CELL_SIZE << ") ===\n";
    std::cout << "D - Дракон, E - Эльф, K - Рыцарь, . - пусто\n\n";
    
    // Вывод карты
    for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < DISPLAY_WIDTH; ++x) {
            char symbol = get_cell_symbol(dragon_counts[x][y], 
                                          elf_counts[x][y], 
                                          knight_counts[x][y]);
            std::cout << symbol;
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

char MapPrinter::get_cell_symbol(int dragons, int elves, int knights) const {
    if (dragons > 0 && dragons >= elves && dragons >= knights) return 'D';
    if (elves > 0 && elves >= dragons && elves >= knights) return 'E';
    if (knights > 0 && knights >= dragons && knights >= elves) return 'K';
    return '.';
}

void MapPrinter::print_survivors(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    
    std::cout << "\n=== ВЫЖИВШИЕ NPC ===" << std::endl;
    int survivors = 0;
    
    for (const auto& npc : npcs) {
        if (npc->is_alive()) {
            npc->print();
            survivors++;
        }
    }
    
    std::cout << "\nВсего выжило: " << survivors << " NPC" << std::endl;
}