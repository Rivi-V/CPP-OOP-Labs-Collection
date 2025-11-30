#include "concrete_fight_visitor.h"
#include "npc.h"

bool ConcreteFightVisitor::visit(Dragon* defender, const std::shared_ptr<NPC>& attacker) {
    if (attacker->type == KnightErrantType) {
        return true; 
    }
    return false;
}

bool ConcreteFightVisitor::visit(Elf* defender, const std::shared_ptr<NPC>& attacker) {
    if (attacker->type == DragonType) {
        return true;
    }
    return false;
}

bool ConcreteFightVisitor::visit(KnightErrant* defender, const std::shared_ptr<NPC>& attacker) {
    if (attacker->type == ElfType) {
        return true;
    }
    return false;
}