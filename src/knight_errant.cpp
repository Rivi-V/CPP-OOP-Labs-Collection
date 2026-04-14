#include "knight_errant.h"
#include "battle_visitor.h"
#include <shared_mutex>
#include <iostream>

KnightErrant::KnightErrant(int x, int y, const std::string& name,
                           int armor, int sword_power,
                           int move_dist, int kill_dist)
    : NPC(NpcType::KnightType, x, y, name, move_dist, kill_dist),
      armor(armor), sword_power(sword_power) {}

bool KnightErrant::accept(std::shared_ptr<Visitor> visitor) {
    return visitor->visit(this);
}

void KnightErrant::print() const {
    std::shared_lock<std::shared_mutex> lock(mtx);  // ИЗМЕНИТЕ!
    std::cout << "Knight " << name << " at (" << x << ", " << y << ")"
              << ", Armor: " << armor << ", Sword Power: " << sword_power
              << ", Move: " << move_distance << ", Kill: " << kill_distance 
              << std::endl;
}

void KnightErrant::save(std::ostream& os) const {
    std::shared_lock<std::shared_mutex> lock(mtx);  // ИЗМЕНИТЕ!
    os << "Knight " << x << " " << y << " " << name 
       << " " << armor << " " << sword_power
       << " " << move_distance << " " << kill_distance << std::endl;
}