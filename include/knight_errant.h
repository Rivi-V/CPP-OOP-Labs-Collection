#pragma once
#include "npc.h"
#include "fight_visitor.h"

struct KnightErrant : public NPC
{
    KnightErrant(int x, int y);
    KnightErrant(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;

    bool accept(const std::shared_ptr<NPC>& attacker) override;

    friend std::ostream &operator<<(std::ostream &os, KnightErrant &knight_errant);
};