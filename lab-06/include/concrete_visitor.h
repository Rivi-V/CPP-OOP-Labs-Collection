#pragma once
#include "visitor.h"

struct ConcreteVisitor : public Visitor {
    bool visit(Dragon* defender, const std::shared_ptr<NPC>& attacker) override;
    bool visit(Elf* defender, const std::shared_ptr<NPC>& attacker) override;
    bool visit(KnightErrant* defender, const std::shared_ptr<NPC>& attacker) override;
};