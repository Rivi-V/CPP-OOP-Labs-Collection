#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>

struct NPC;
struct Elf;
struct KnightErrant;
struct Dragon;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    ElfType = 1,
    KnightErrantType = 2,
    DragonType = 3
};

struct IFightObserver{
    virtual void on_fight(const std::shared_ptr<NPC> attacker,const std::shared_ptr<NPC> defender,bool win) = 0;
};

struct FightVisitor;

struct NPC : public std::enable_shared_from_this<NPC>
{
    NpcType type;
    int x{0};
    int y{0};
    bool alive{true}; 
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver>observer);
    void fight_notify(const std::shared_ptr<NPC> defender,bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual bool accept(const std::shared_ptr<NPC>& attacker) = 0;

    virtual void print() = 0;
    virtual void save(std::ostream &os);

    bool isAlive() const { return alive; }
    void setAlive(bool status) { alive = status; }

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};