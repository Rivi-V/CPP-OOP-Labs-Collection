#include "battle_visitor.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include "npc.h"  // Теперь можно включить
#include <iostream>
#include <shared_mutex>

BattleVisitor::BattleVisitor(NpcType type, const std::string& name) 
    : attacker_type(type), attacker_name(name) {}

bool BattleVisitor::visit(Dragon* dragon) {
    // Определяем, может ли атакующий атаковать дракона
    switch (attacker_type) {
        case NpcType::DragonType:
            // Драконы могут атаковать друг друга
            return true;
        case NpcType::ElfType:
            // Эльфы не атакуют драконов
            return false;
        case NpcType::KnightType:
            // Рыцари могут атаковать драконов
            return true;
        default:
            return false;
    }
}

bool BattleVisitor::visit(Elf* elf) {
    switch (attacker_type) {
        case NpcType::DragonType:
            // Драконы могут атаковать эльфов
            return true;
        case NpcType::ElfType:
            // Эльфы не атакуют друг друга
            return false;
        case NpcType::KnightType:
            // Рыцари не атакуют эльфов
            return false;
        default:
            return false;
    }
}

bool BattleVisitor::visit(KnightErrant* knight) {
    switch (attacker_type) {
        case NpcType::DragonType:
            return true;
        case NpcType::ElfType:
            return true;
        case NpcType::KnightType:
            return false;
        default:
            return false;
    }
}