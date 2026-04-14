#pragma once
#include <memory>
#include "npc.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"

class FightVisitor {
public:
    virtual bool visit(Dragon* defender, const std::shared_ptr<NPC>& attacker) = 0;
    virtual bool visit(Elf* defender, const std::shared_ptr<NPC>& attacker) = 0;
    virtual bool visit(KnightErrant* defender, const std::shared_ptr<NPC>& attacker) = 0;
    virtual ~FightVisitor() = default;
};  

class ConcreteFightVisitor : public FightVisitor {
public:
    bool visit(Dragon* defender, const std::shared_ptr<NPC>& attacker) override {
        // Рыцарь убивает дракона
        if (attacker->type == KnightErrantType) {
            return true;
        }
        // Дракон убивает дракона
        else if (attacker->type == DragonType) {
            return true;
        }
        return false;
    }

    bool visit(Elf* defender, const std::shared_ptr<NPC>& attacker) override {
        // Дракон убивает эльфа
        if (attacker->type == DragonType) {
            return true;
        }
        return false;
    }

    bool visit(KnightErrant* defender, const std::shared_ptr<NPC>& attacker) override {
        // Эльф убивает рыцаря
        if (attacker->type == ElfType) {
            return true;
        }
        // Дракон убивает рыцаря
        else if (attacker->type == DragonType) {
            return true;
        }
        return false;
    }
};