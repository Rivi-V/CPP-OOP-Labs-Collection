#pragma once
#include "visitor.h"
#include <string>

// Предварительные объявления
class Dragon;
class Elf;
class KnightErrant;

// Объявление NpcType (так как npc.h не может быть включен из-за циклических зависимостей)
enum class NpcType;

class BattleVisitor : public Visitor {
private:
    NpcType attacker_type;
    std::string attacker_name;
    
public:
    BattleVisitor(NpcType type, const std::string& name);
    
    bool visit(Dragon* dragon) override;
    bool visit(Elf* elf) override;
    bool visit(KnightErrant* knight) override;
};