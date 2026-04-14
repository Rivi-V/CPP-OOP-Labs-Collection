#pragma once
#include "npc.h"
#include "visitor.h"

class Dragon : public NPC {
public:
    Dragon(int x, int y, const std::string& name,
           int move_dist = 50, int kill_dist = 30);
    bool accept(std::shared_ptr<Visitor> visitor) override;
    void print() const override;
    void save(std::ostream& os) const override;
};