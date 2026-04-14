#include "elf.h"
#include "battle_visitor.h"
#include <iostream>
#include <shared_mutex>


Elf::Elf(int x, int y, const std::string& name,
         int move_dist, int kill_dist)
    : NPC(NpcType::ElfType, x, y, name, move_dist, kill_dist) {}

bool Elf::accept(std::shared_ptr<Visitor> visitor) {
    return visitor->visit(this);
}

void Elf::print() const {
    std::shared_lock<std::shared_mutex> lock(mtx);  // ИЗМЕНИТЕ!
    std::cout << "Elf " << name << " at (" << x << ", " << y << ")"
              << ", Move: " << move_distance << ", Kill: " << kill_distance 
              << std::endl;
}

void Elf::save(std::ostream& os) const {
    std::shared_lock<std::shared_mutex> lock(mtx);  // ИЗМЕНИТЕ!
    os << "Elf " << x << " " << y << " " << name 
       << " " << move_distance << " " << kill_distance << std::endl;
}