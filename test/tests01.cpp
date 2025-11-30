#include <gtest/gtest.h>
#include <memory>
#include "npc.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include "concrete_fight_visitor.h"

TEST(BasicTest, NPCCreation) {
    Dragon dragon(100, 200);
    Elf elf(50, 75);
    KnightErrant knight(300, 400);
    
    ASSERT_EQ(dragon.type, DragonType);
    ASSERT_EQ(elf.type, ElfType);
    ASSERT_EQ(knight.type, KnightErrantType);
}

TEST(BasicTest, IsCloseMethod) {
    auto npc1 = std::make_shared<Dragon>(0, 0);
    auto npc2 = std::make_shared<Elf>(3, 4);
    
    ASSERT_TRUE(npc1->is_close(npc2, 5));
    ASSERT_FALSE(npc1->is_close(npc2, 4));
}

TEST(BasicTest, AliveState) {
    auto dragon = std::make_shared<Dragon>(0, 0);
    ASSERT_TRUE(dragon->isAlive());
    
    dragon->setAlive(false);
    ASSERT_FALSE(dragon->isAlive());
}

TEST(VisitorTest, BasicFightRules) {
    ConcreteFightVisitor visitor;
    auto dragon = std::make_shared<Dragon>(0, 0);
    auto elf = std::make_shared<Elf>(0, 0);
    auto knight = std::make_shared<KnightErrant>(0, 0);
    
    ASSERT_TRUE(visitor.visit(static_cast<Dragon*>(dragon.get()), knight));
    ASSERT_TRUE(visitor.visit(static_cast<KnightErrant*>(knight.get()), elf));
    ASSERT_FALSE(visitor.visit(static_cast<Dragon*>(dragon.get()), elf));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}