#include "knight_errant.h"

KnightErrant::KnightErrant(int x, int y) : NPC(KnightErrantType, x, y) {}
KnightErrant::KnightErrant(std::istream &is) : NPC(KnightErrantType, is) {}

void KnightErrant::print() {
    std::cout << "KnightErrant at (" << x << ", " << y << ")" << std::endl;
}

bool KnightErrant::accept(const std::shared_ptr<NPC>& attacker) {
    ConcreteFightVisitor visitor;
    return visitor.visit(this, attacker);
}

void KnightErrant::save(std::ostream &os) {
    os << KnightErrantType << " ";
    NPC::save(os);
}