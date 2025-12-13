#pragma once
#include "npc.h"
#include "visitor.h"

struct KnightErrant : public NPC {
    KnightErrant(int x, int y);
    KnightErrant(std::istream &is);
    
    void print() override;
    bool accept(const std::shared_ptr<NPC>& attacker) override;
    void save(std::ostream &os) override;
};