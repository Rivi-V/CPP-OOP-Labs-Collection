#pragma once
#include <memory>

struct NPC;
struct Dragon;
struct Elf;
struct KnightErrant;

struct FightVisitor {
    virtual bool visit(Dragon* defender, const std::shared_ptr<NPC>& attacker) = 0;
    virtual bool visit(Elf* defender, const std::shared_ptr<NPC>& attacker) = 0;
    virtual bool visit(KnightErrant* defender, const std::shared_ptr<NPC>& attacker) = 0;
    virtual ~FightVisitor() = default;
};