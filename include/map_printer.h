#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "npc.h"

class MapPrinter {
private:
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;
    const int CELL_SIZE = 5;
    const int DISPLAY_WIDTH = MAP_WIDTH / CELL_SIZE;
    const int DISPLAY_HEIGHT = MAP_HEIGHT / CELL_SIZE;

    
public:
    MapPrinter() = default;
    
    // ОДИН аргумент!
    void print_map(const std::vector<std::shared_ptr<NPC>>& npcs);
    void print_survivors(const std::vector<std::shared_ptr<NPC>>& npcs);
    
private:
    char get_cell_symbol(int dragons, int elves, int knights) const;
};