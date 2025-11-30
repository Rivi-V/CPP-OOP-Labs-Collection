#include "knight_errant.h"
#include "dragon.h"
#include "elf.h"
#include "concrete_fight_visitor.h"

KnightErrant::KnightErrant(int x, int y) : NPC(KnightErrantType, x, y) {}
KnightErrant::KnightErrant(std::istream &is) : NPC(KnightErrantType, is) {}

void KnightErrant::print()
{
    std::cout << *this;
}

void KnightErrant::save(std::ostream &os)
{
    os << KnightErrantType << std::endl;
    NPC::save(os);
}

bool KnightErrant::accept(const std::shared_ptr<NPC>& attacker) {
    ConcreteFightVisitor visitor;
    return visitor.visit(this, attacker);
}

std::ostream &operator<<(std::ostream &os, KnightErrant &knight_errant)
{
    os << "knight_errant: " << *static_cast<NPC *>(&knight_errant) << std::endl;
    return os;
}