#pragma once
#include "npc.h"
#include "visitor.h"

class Elf : public NPC {
public:
    Elf(int x, int y, const std::string& name,
        int move_dist = 10, int kill_dist = 50);
    bool accept(std::shared_ptr<Visitor> visitor) override;
    void print() const override;
    void save(std::ostream& os) const override;
};