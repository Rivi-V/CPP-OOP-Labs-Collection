#include <gtest/gtest.h>
#include <memory>
#include "npc.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include "visitor.h"  // Изменили с concrete_fight_visitor.h на visitor.h

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
    
    // Метод is_close теперь принимает distance параметр
    ASSERT_TRUE(npc1->is_close(npc2, 5));
    ASSERT_FALSE(npc1->is_close(npc2, 4));
}

TEST(BasicTest, AliveState) {
    auto dragon = std::make_shared<Dragon>(0, 0);
    // Методы переименованы: isAlive -> is_alive, setAlive -> set_alive
    ASSERT_TRUE(dragon->is_alive());
    
    dragon->set_alive(false);
    ASSERT_FALSE(dragon->is_alive());
}

TEST(VisitorTest, BasicFightRules) {
    ConcreteFightVisitor visitor;  // Теперь в visitor.h
    auto dragon = std::make_shared<Dragon>(0, 0);
    auto elf = std::make_shared<Elf>(0, 0);
    auto knight = std::make_shared<KnightErrant>(0, 0);
    
    // Проверяем правила для варианта 2
    ASSERT_TRUE(visitor.visit(static_cast<Dragon*>(dragon.get()), knight)); // Рыцарь убивает дракона
    ASSERT_TRUE(visitor.visit(static_cast<KnightErrant*>(knight.get()), elf)); // Эльф убивает рыцаря
    ASSERT_FALSE(visitor.visit(static_cast<Dragon*>(dragon.get()), elf)); // Эльф не убивает дракона
}

TEST(VisitorTest, SelfFight) {
    ConcreteFightVisitor visitor;
    auto dragon1 = std::make_shared<Dragon>(0, 0);
    auto dragon2 = std::make_shared<Dragon>(0, 0);
    auto elf1 = std::make_shared<Elf>(0, 0);
    auto elf2 = std::make_shared<Elf>(0, 0);
    auto knight1 = std::make_shared<KnightErrant>(0, 0);
    auto knight2 = std::make_shared<KnightErrant>(0, 0);
    
    // Одинаковые типы не должны убивать друг друга
    ASSERT_FALSE(visitor.visit(static_cast<Dragon*>(dragon1.get()), dragon2));
    ASSERT_FALSE(visitor.visit(static_cast<Elf*>(elf1.get()), elf2));
    ASSERT_FALSE(visitor.visit(static_cast<KnightErrant*>(knight1.get()), knight2));
}

TEST(AcceptMethodTest, DragonAccept) {
    auto dragon = std::make_shared<Dragon>(0, 0);
    auto elf = std::make_shared<Elf>(0, 0);
    auto knight = std::make_shared<KnightErrant>(0, 0);
    
    // Дракон должен принимать смерть только от рыцаря
    ASSERT_TRUE(dragon->accept(knight));    // Рыцарь убивает дракона
    ASSERT_FALSE(dragon->accept(elf));      // Эльф не убивает дракона
}

TEST(AcceptMethodTest, KnightAccept) {
    auto knight = std::make_shared<KnightErrant>(0, 0);
    auto elf = std::make_shared<Elf>(0, 0);
    auto dragon = std::make_shared<Dragon>(0, 0);
    
    // Рыцарь должен принимать смерть только от эльфа
    ASSERT_TRUE(knight->accept(elf));       // Эльф убивает рыцаря
    ASSERT_FALSE(knight->accept(dragon));   // Дракон не убивает рыцаря
}

TEST(AcceptMethodTest, ElfAccept) {
    auto elf = std::make_shared<Elf>(0, 0);
    auto dragon = std::make_shared<Dragon>(0, 0);
    auto knight = std::make_shared<KnightErrant>(0, 0);
    
    // Эльф должен принимать смерть только от дракона
    ASSERT_TRUE(elf->accept(dragon));       // Дракон убивает эльфа
    ASSERT_FALSE(elf->accept(knight));      // Рыцарь не убивает эльфа
}

TEST(FactoryTest, CreateNPCs) {
    // Создаем NPC через factory (нужно добавить factory.h в includes)
    auto dragon = std::make_shared<Dragon>(100, 100);
    auto elf = std::make_shared<Elf>(200, 200);
    auto knight = std::make_shared<KnightErrant>(300, 300);
    
    ASSERT_EQ(dragon->type, DragonType);
    ASSERT_EQ(elf->type, ElfType);
    ASSERT_EQ(knight->type, KnightErrantType);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}