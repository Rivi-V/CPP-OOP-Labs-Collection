#pragma once
#include "npc.h"
#include "visitor.h"

struct Dragon : public NPC {
    Dragon(int x, int y);
    Dragon(std::istream &is);
    
    void print() override;
    bool accept(const std::shared_ptr<NPC>& attacker) override;
    void save(std::ostream &os) override;
};