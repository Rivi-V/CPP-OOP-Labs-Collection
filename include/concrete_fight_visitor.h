#pragma once
#include "fight_visitor.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"

struct ConcreteFightVisitor : public FightVisitor {
    bool visit(Dragon* defender, const std::shared_ptr<NPC>& attacker) override;
    bool visit(Elf* defender, const std::shared_ptr<NPC>& attacker) override;
    bool visit(KnightErrant* defender, const std::shared_ptr<NPC>& attacker) override;
};