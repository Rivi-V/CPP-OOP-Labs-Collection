#pragma once
#include "npc.h"
#include "visitor.h"

struct Elf : public NPC {
    Elf(int x, int y);
    Elf(std::istream &is);
    
    void print() override;
    bool accept(const std::shared_ptr<NPC>& attacker) override;
    void save(std::ostream &os) override;
};