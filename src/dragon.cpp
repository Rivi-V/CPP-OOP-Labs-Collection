#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include "concrete_fight_visitor.h"

Dragon::Dragon(int x, int y) : NPC(DragonType, x, y) {}
Dragon::Dragon(std::istream &is) : NPC(DragonType, is) {}

void Dragon::print()
{
    std::cout << *this;
}

bool Dragon::accept(const std::shared_ptr<NPC>& attacker) {
    ConcreteFightVisitor visitor;
    return visitor.visit(this, attacker);
}

void Dragon::save(std::ostream &os) 
{
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Dragon &dragon)
{
    os << "dragon: " << *static_cast<NPC *>(&dragon) << std::endl;
    return os;
}