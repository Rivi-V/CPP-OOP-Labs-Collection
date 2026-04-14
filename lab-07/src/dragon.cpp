#include "dragon.h"
#include "battle_visitor.h"
#include <iostream>
#include <shared_mutex>


Dragon::Dragon(int x, int y, const std::string& name,
               int move_dist, int kill_dist)
    : NPC(NpcType::DragonType, x, y, name, move_dist, kill_dist) {}

bool Dragon::accept(std::shared_ptr<Visitor> visitor) {
    return visitor->visit(this);
}

void Dragon::print() const {
    std::shared_lock<std::shared_mutex> lock(mtx);  // ИЗМЕНИТЕ!
    std::cout << "Dragon " << name << " at (" << x << ", " << y << ")"
              << ", Move: " << move_distance << ", Kill: " << kill_distance 
              << std::endl;
}

void Dragon::save(std::ostream& os) const {
    std::shared_lock<std::shared_mutex> lock(mtx);  // ИЗМЕНИТЕ!
    os << "Dragon " << x << " " << y << " " << name 
       << " " << move_distance << " " << kill_distance << std::endl;
}