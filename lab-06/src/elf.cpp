#include "elf.h"

Elf::Elf(int x, int y) : NPC(ElfType, x, y) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

void Elf::print() {
    std::cout << "Elf at (" << x << ", " << y << ")" << std::endl;
}

bool Elf::accept(const std::shared_ptr<NPC>& attacker) { // принимает attacker
    ConcreteFightVisitor visitor;
    return visitor.visit(this, attacker);
}

void Elf::save(std::ostream &os) {
    os << ElfType << " ";
    NPC::save(os);
}