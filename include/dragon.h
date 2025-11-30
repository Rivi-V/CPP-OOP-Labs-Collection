#pragma once
#include "npc.h"
#include "fight_visitor.h"

struct Dragon : public NPC
{
    Dragon(int x, int y);
    Dragon(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;

    bool accept(const std::shared_ptr<NPC>& attacker) override;

    friend std::ostream &operator<<(std::ostream &os, Dragon &dragon);
};