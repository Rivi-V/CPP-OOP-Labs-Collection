#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <atomic>
#include "npc.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include "factory.h"
#include "observer.h"
#include "battle_visitor.h"
#include "helpers.h"
#include "fight_manager.h"
#include "npc_type.h"
#include "common.h"

namespace fs = std::filesystem;

// ==================== Базовые тесты NPC ====================

TEST(NPCTest, CreationAndTypes) {
    auto dragon = Factory::create(NpcType::DragonType, 100, 200, "TestDragon", 50, 30);
    auto elf = Factory::create(NpcType::ElfType, 50, 75, "TestElf", 10, 50);
    auto knight = Factory::create(NpcType::KnightType, 300, 400, "TestKnight", 30, 10);
    
    ASSERT_EQ(dragon->get_type(), NpcType::DragonType);
    ASSERT_EQ(elf->get_type(), NpcType::ElfType);
    ASSERT_EQ(knight->get_type(), NpcType::KnightType);
    
    ASSERT_EQ(dragon->get_move_distance(), 50);
    ASSERT_EQ(elf->get_move_distance(), 10);
    ASSERT_EQ(knight->get_move_distance(), 30);
    
    ASSERT_EQ(dragon->get_kill_distance(), 30);
    ASSERT_EQ(elf->get_kill_distance(), 50);
    ASSERT_EQ(knight->get_kill_distance(), 10);
}

TEST(NPCTest, MoveMethod) {
    auto dragon = Factory::create(NpcType::DragonType, 50, 50, "TestDragon", 10, 5);
    
    // Многократно двигаем и проверяем границы
    for (int i = 0; i < 100; ++i) {
        dragon->move(100, 100);
        
        int x = dragon->get_x();
        int y = dragon->get_y();
        
        ASSERT_GE(x, 0);
        ASSERT_LT(x, 100);
        ASSERT_GE(y, 0);
        ASSERT_LT(y, 100);
    }
}

TEST(NPCTest, IsCloseMethod) {
    auto npc1 = Factory::create(NpcType::DragonType, 0, 0, "Dragon1", 10, 100);
    auto npc2 = Factory::create(NpcType::ElfType, 8, 8, "Elf1", 10, 100);
    auto npc3 = Factory::create(NpcType::KnightType, 200, 200, "Knight1", 10, 100);
    
    // npc1 и npc2 должны быть близко (расстояние ≈ 11.3, kill_distance = 100)
    ASSERT_TRUE(npc1->is_close(npc2));
    
    // npc1 и npc3 должны быть далеко
    ASSERT_FALSE(npc1->is_close(npc3));
}

TEST(NPCTest, AliveStatus) {
    auto npc = Factory::create(NpcType::DragonType, 0, 0, "TestNPC", 10, 10);
    
    ASSERT_TRUE(npc->is_alive());
    
    npc->set_alive(false);
    ASSERT_FALSE(npc->is_alive());
}

// ==================== Тесты броска кубиков ====================

TEST(DiceTest, RollDiceRange) {
    // Бросаем кубик много раз и проверяем диапазон
    for (int i = 0; i < 1000; ++i) {
        int roll = NPC::roll_dice();
        ASSERT_GE(roll, 1);
        ASSERT_LE(roll, 6);
    }
}

// ==================== Тесты фабрики ====================

TEST(FactoryTest, CreateNPCs) {
    auto dragon = Factory::create(NpcType::DragonType, 0, 0, "Dragon");
    ASSERT_NE(dragon, nullptr);
    ASSERT_EQ(dragon->get_type(), NpcType::DragonType);
    
    auto elf = Factory::create(NpcType::ElfType, 0, 0, "Elf");
    ASSERT_NE(elf, nullptr);
    ASSERT_EQ(elf->get_type(), NpcType::ElfType);
    
    auto knight = Factory::create(NpcType::KnightType, 0, 0, "Knight");
    ASSERT_NE(knight, nullptr);
    ASSERT_EQ(knight->get_type(), NpcType::KnightType);
}

TEST(FactoryTest, LoadNPCFromStream) {
    std::stringstream ss;
    ss << "Dragon 10 20 Dragon1 50 30";
    
    auto npc = Factory::load(ss);
    ASSERT_NE(npc, nullptr);
    ASSERT_EQ(npc->get_type(), NpcType::DragonType);
    ASSERT_EQ(npc->get_x(), 10);
    ASSERT_EQ(npc->get_y(), 20);
    ASSERT_EQ(npc->get_name(), "Dragon1");
    ASSERT_EQ(npc->get_move_distance(), 50);
    ASSERT_EQ(npc->get_kill_distance(), 30);
}

// ==================== Тесты Visitor ====================

TEST(VisitorTest, DragonAttackRules) {
    auto dragon_visitor = std::make_shared<BattleVisitor>(NpcType::DragonType, "Dragon");
    
    auto dragon = std::make_shared<Dragon>(0, 0, "TargetDragon");
    auto elf = std::make_shared<Elf>(0, 0, "TargetElf");
    auto knight = std::make_shared<KnightErrant>(0, 0, "TargetKnight");
    
    // Дракон может атаковать всех
    ASSERT_TRUE(dragon->accept(dragon_visitor));
    ASSERT_TRUE(elf->accept(dragon_visitor));
    ASSERT_TRUE(knight->accept(dragon_visitor));
}

TEST(VisitorTest, ElfAttackRules) {
    auto elf_visitor = std::make_shared<BattleVisitor>(NpcType::ElfType, "Elf");
    
    auto dragon = std::make_shared<Dragon>(0, 0, "TargetDragon");
    auto elf = std::make_shared<Elf>(0, 0, "TargetElf");
    auto knight = std::make_shared<KnightErrant>(0, 0, "TargetKnight");
    
    // Эльф может атаковать только рыцарей
    ASSERT_FALSE(dragon->accept(elf_visitor));
    ASSERT_FALSE(elf->accept(elf_visitor));
    ASSERT_TRUE(knight->accept(elf_visitor));
}

TEST(VisitorTest, KnightAttackRules) {
    auto knight_visitor = std::make_shared<BattleVisitor>(NpcType::KnightType, "Knight");
    
    auto dragon = std::make_shared<Dragon>(0, 0, "TargetDragon");
    auto elf = std::make_shared<Elf>(0, 0, "TargetElf");
    auto knight = std::make_shared<KnightErrant>(0, 0, "TargetKnight");
    
    // Рыцарь может атаковать только драконов
    ASSERT_TRUE(dragon->accept(knight_visitor));
    ASSERT_FALSE(elf->accept(knight_visitor));
    ASSERT_FALSE(knight->accept(knight_visitor));
}

// ==================== Тесты Observer ====================

TEST(ObserverTest, ConsoleObserverCreation) {
    auto observer = std::make_shared<ConsoleObserver>();
    ASSERT_NE(observer, nullptr);
}

TEST(ObserverTest, FileObserverCreation) {
    auto observer = std::make_shared<FileObserver>("test_log.txt");
    ASSERT_NE(observer, nullptr);
    
    // Проверяем, что файл создался
    std::ifstream file("test_log.txt");
    ASSERT_TRUE(file.is_open());
    file.close();
    
    // Удаляем тестовый файл
    std::remove("test_log.txt");
}

TEST(ObserverTest, ObservableAddNotify) {
    auto observable = std::make_shared<Observable>();
    auto observer = std::make_shared<ConsoleObserver>();
    
    observable->add_observer(observer);
    
    auto attacker = Factory::create(NpcType::DragonType, 0, 0, "Attacker");
    auto defender = Factory::create(NpcType::ElfType, 0, 0, "Defender");
    
    // Этот вызов не должен падать
    observable->notify(attacker, defender, true);
    
    ASSERT_TRUE(true); // Если мы дошли сюда, значит все ок
}

// ==================== Тесты FightManager ====================

TEST(FightManagerTest, Creation) {
    auto observable = std::make_shared<Observable>();
    auto fight_manager = std::make_shared<FightManager>(observable);
    
    ASSERT_NE(fight_manager, nullptr);
}

TEST(FightManagerTest, AddEvent) {
    auto observable = std::make_shared<Observable>();
    auto fight_manager = std::make_shared<FightManager>(observable);
    
    auto attacker = Factory::create(NpcType::DragonType, 0, 0, "Attacker");
    auto defender = Factory::create(NpcType::ElfType, 0, 0, "Defender");
    
    // Этот вызов не должен падать
    fight_manager->add_event(attacker, defender);
    
    ASSERT_TRUE(true);
}

// ==================== Тесты многопоточности ====================

TEST(ConcurrencyTest, MultipleThreadsMove) {
    std::vector<std::shared_ptr<NPC>> npcs;
    for (int i = 0; i < 10; ++i) {
        npcs.push_back(Factory::create(NpcType::DragonType, i*10, i*10, "NPC" + std::to_string(i)));
    }
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&npcs]() {
            for (int j = 0; j < 10; ++j) {
                for (auto& npc : npcs) {
                    if (npc->is_alive()) {
                        npc->move(100, 100);
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Все NPC должны остаться в границах карты
    for (const auto& npc : npcs) {
        int x = npc->get_x();
        int y = npc->get_y();
        ASSERT_GE(x, 0);
        ASSERT_LT(x, 100);
        ASSERT_GE(y, 0);
        ASSERT_LT(y, 100);
    }
}

TEST(ConcurrencyTest, FightManagerThread) {
    auto observable = std::make_shared<Observable>();
    auto fight_manager = std::make_shared<FightManager>(observable);
    
    // Создаем несколько NPC для боев
    std::vector<std::shared_ptr<NPC>> npcs;
    for (int i = 0; i < 5; ++i) {
        npcs.push_back(Factory::create(NpcType::DragonType, i*10, i*10, "Dragon" + std::to_string(i)));
        npcs.push_back(Factory::create(NpcType::ElfType, i*10 + 5, i*10 + 5, "Elf" + std::to_string(i)));
    }
    
    // Добавляем события боя
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            fight_manager->add_event(npcs[i], npcs[j]);
        }
    }
    
    // Запускаем обработчик в отдельном потоке
    std::atomic<bool> running{true};
    std::thread processor([&]() {
        fight_manager->process_events(running);
    });
    
    // Даем время на обработку
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Останавливаем
    running = false;
    processor.join();
    
    ASSERT_TRUE(true); // Если дошли сюда, все ок
}

// ==================== Тесты для варианта 2 ====================

TEST(Variant2Test, DragonCharacteristics) {
    auto dragon = Factory::create(NpcType::DragonType, 0, 0, "Dragon");
    
    ASSERT_EQ(dragon->get_move_distance(), 50);  // Из таблицы
    ASSERT_EQ(dragon->get_kill_distance(), 30);  // Из таблицы
}

TEST(Variant2Test, ElfCharacteristics) {
    auto elf = Factory::create(NpcType::ElfType, 0, 0, "Elf");
    
    ASSERT_EQ(elf->get_move_distance(), 10);  // Из таблицы
    ASSERT_EQ(elf->get_kill_distance(), 50);  // Из таблицы
}

TEST(Variant2Test, KnightCharacteristics) {
    auto knight = Factory::create(NpcType::KnightType, 0, 0, "Knight");
    
    ASSERT_EQ(knight->get_move_distance(), 30);  // Из таблицы
    ASSERT_EQ(knight->get_kill_distance(), 10);  // Из таблицы
}

// ==================== Интеграционные тесты ====================

TEST(IntegrationTest, CompleteSimulationShort) {
    // Создаем NPC
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(Factory::create(NpcType::DragonType, 10, 10, "Dragon1"));
    npcs.push_back(Factory::create(NpcType::ElfType, 15, 15, "Elf1"));
    npcs.push_back(Factory::create(NpcType::KnightType, 12, 12, "Knight1"));
    
    // Создаем систему
    auto observable = std::make_shared<Observable>();
    auto console_observer = std::make_shared<ConsoleObserver>();
    observable->add_observer(console_observer);
    
    auto fight_manager = std::make_shared<FightManager>(observable);
    
    // Запускаем потоки на короткое время
    std::atomic<bool> running{true};
    
    std::thread movement([&]() {
        for (int i = 0; i < 5 && running.load(); ++i) {
            for (auto& npc : npcs) {
                if (npc->is_alive()) {
                    npc->move(100, 100);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });
    
    std::thread fight_processor([&]() {
        fight_manager->process_events(running);
    });
    
    // Даем системе поработать
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    // Останавливаем
    running = false;
    fight_manager->stop();
    
    movement.join();
    fight_processor.join();
    
    // Проверяем, что программа не упала
    ASSERT_TRUE(true);
}

TEST(HelpersTest, TypeToString) {
    ASSERT_EQ(type_to_string(NpcType::DragonType), "Dragon");
    ASSERT_EQ(type_to_string(NpcType::ElfType), "Elf");
    ASSERT_EQ(type_to_string(NpcType::KnightType), "Knight");
}

int main(int argc, char **argv) {
    std::cout << "==========================================" << std::endl;
    std::cout << "🧪 ЗАПУСК ТЕСТОВ NPC SIMULATOR (ЛАБ 7)" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    testing::InitGoogleTest(&argc, argv);
    
    // Создаем временную директорию для тестовых файлов
    if (!fs::exists("test_output")) {
        fs::create_directory("test_output");
    }
    
    int result = RUN_ALL_TESTS();
    
    // Очищаем временные файлы
    try {
        if (fs::exists("test_log.txt")) {
            fs::remove("test_log.txt");
        }
        if (fs::exists("test_output")) {
            fs::remove_all("test_output");
        }
    } catch (...) {
        // Игнорируем ошибки очистки
    }
    
    std::cout << "==========================================" << std::endl;
    if (result == 0) {
        std::cout << "✅ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << std::endl;
    } else {
        std::cout << "❌ ТЕСТЫ НЕ ПРОЙДЕНЫ!" << std::endl;
    }
    std::cout << "==========================================" << std::endl;
    
    return result;
}