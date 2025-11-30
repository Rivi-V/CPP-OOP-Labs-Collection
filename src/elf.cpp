#include "elf.h"
#include "dragon.h"
#include "knight_errant.h"
#include "concrete_fight_visitor.h"

Elf::Elf(int x, int y) : NPC(ElfType, x, y) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

void Elf::print()
{
    std::cout << *this;
}

bool Elf::accept(const std::shared_ptr<NPC>& attacker) {
    ConcreteFightVisitor visitor;
    return visitor.visit(this, attacker);
}

void Elf::save(std::ostream &os) 
{
    os << ElfType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Elf &elf)
{
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}