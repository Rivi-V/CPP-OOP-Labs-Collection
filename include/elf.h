#pragma once
#include "npc.h"
#include "fight_visitor.h"

struct Elf : public NPC
{
    Elf(int x, int y);
    Elf(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    
    bool accept(const std::shared_ptr<NPC>& attacker) override;

    friend std::ostream &operator<<(std::ostream &os, Elf &elf);
};