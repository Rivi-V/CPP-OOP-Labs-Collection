#include "dragon.h"

Dragon::Dragon(int x, int y) : NPC(DragonType, x, y) {}
Dragon::Dragon(std::istream &is) : NPC(DragonType, is) {}

void Dragon::print() {
    std::cout << "Dragon at (" << x << ", " << y << ")" << std::endl;
}

bool Dragon::accept(const std::shared_ptr<NPC>& attacker) {
    ConcreteFightVisitor visitor;
    return visitor.visit(this, attacker);
}

void Dragon::save(std::ostream &os) {
    os << DragonType << " ";
    NPC::save(os);
}