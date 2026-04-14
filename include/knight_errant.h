#pragma once
#include "npc.h"
#include "visitor.h"

class KnightErrant : public NPC {
public:
    KnightErrant(int x, int y, const std::string& name,
                 int armor = 50, int sword_power = 30,
                 int move_dist = 30, int kill_dist = 10);
    bool accept(std::shared_ptr<Visitor> visitor) override;
    void print() const override;
    void save(std::ostream& os) const override;
    
private:
    int armor;
    int sword_power;
};