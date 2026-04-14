#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <random>
#include <algorithm>
#include "factory.h"
#include "observer.h"
#include "fight_manager.h"
#include "map_printer.h"
#include "common.h"
#include "npc_type.h"  // Добавьте эту строку после других includes

// Функция для потока движения
void movement_thread(std::vector<std::shared_ptr<NPC>>& npcs,
                     std::shared_ptr<FightManager> fight_manager,
                     const std::atomic<bool>& running,
                     int map_width, int map_height) {
    while (running.load()) {
        for (auto& npc : npcs) {
            if (npc->is_alive()) {
                npc->move(map_width, map_height);
            }
        }

        // Обнаружение близких NPC для боя
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!npcs[i]->is_alive()) continue;

            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[j]->is_alive()) continue;

                // Проверяем близость (расстояние убийства из таблицы)
                if (npcs[i]->is_close(npcs[j])) {
                    // Добавляем событие боя в очередь
                    fight_manager->add_event(npcs[i], npcs[j]);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Функция для создания случайных NPC
void create_random_npcs(std::vector<std::shared_ptr<NPC>>& npcs, int count,
                       int map_width, int map_height) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 2);
    std::uniform_int_distribution<> x_dist(0, map_width - 1);
    std::uniform_int_distribution<> y_dist(0, map_height - 1);
    std::uniform_int_distribution<> name_dist(1000, 9999);

    for (int i = 0; i < count; ++i) {
        NpcType type = static_cast<NpcType>(type_dist(gen));
        int x = x_dist(gen);
        int y = y_dist(gen);
        std::string name;

        // Создаем NPC с параметрами из таблицы
        switch (type) {
            case NpcType::DragonType:
                name = "Dragon_" + std::to_string(name_dist(gen));
                npcs.push_back(Factory::create(type, x, y, name, 50, 30));
                break;
            case NpcType::ElfType:
                name = "Elf_" + std::to_string(name_dist(gen));
                npcs.push_back(Factory::create(type, x, y, name, 10, 50));
                break;
            case NpcType::KnightType:
                name = "Knight_" + std::to_string(name_dist(gen));
                npcs.push_back(Factory::create(type, x, y, name, 30, 10));
                break;
        }
    }
}

int main() {
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;
    const int GAME_DURATION = 30; // 30 секунд согласно заданию
    const int NPC_COUNT = 50;     // 50 NPC согласно заданию

    std::cout << "==========================================" << std::endl;
    std::cout << "🎮 МНОГОПОТОЧНАЯ СИМУЛЯЦИЯ БОЁВ NPC" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Вариант 2: Дракон, Эльф, Странствующий рыцарь" << std::endl;
    std::cout << "Длительность: " << GAME_DURATION << " секунд" << std::endl;
    std::cout << "Карта: " << MAP_WIDTH << "x" << MAP_HEIGHT << std::endl;
    std::cout << "NPC: " << NPC_COUNT << " случайных" << std::endl;
    std::cout << "==========================================" << std::endl;

    // Создаем наблюдателей
    auto console_observer = std::make_shared<ConsoleObserver>();
    auto file_observer = std::make_shared<FileObserver>("battle_log.txt");
    auto observable = std::make_shared<Observable>();
    observable->add_observer(console_observer);
    observable->add_observer(file_observer);

    // Создаем менеджер боёв
    auto fight_manager = std::make_shared<FightManager>(observable);

    // Создаем принтер карты
    MapPrinter map_printer;

    // Создаем NPC
    std::vector<std::shared_ptr<NPC>> npcs;
    create_random_npcs(npcs, NPC_COUNT, MAP_WIDTH, MAP_HEIGHT);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\nСоздано " << npcs.size() << " NPC" << std::endl;
    }

    // Запускаем потоки
    std::atomic<bool> running{true};

    std::thread movement([&]() {
        movement_thread(npcs, fight_manager, running, MAP_WIDTH, MAP_HEIGHT);
    });

    std::thread fight_processor([&]() {
        fight_manager->process_events(running);
    });

    // Главный поток - отображение карты
    auto start_time = std::chrono::steady_clock::now();
    int seconds_passed = 0;

    while (seconds_passed < GAME_DURATION) {
        auto current_time = std::chrono::steady_clock::now();
        seconds_passed = std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count();

        map_printer.print_map(npcs);

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Время: " << seconds_passed << "/" << GAME_DURATION << " сек" << std::endl;
            std::cout << "Живых NPC: " 
                << std::count_if(npcs.begin(), npcs.end(),
                               [](const auto& npc) { return npc->is_alive(); })
                << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Останавливаем симуляцию
    running = false;
    fight_manager->stop();

    movement.join();
    fight_processor.join();

    // Финальный вывод
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\n==========================================" << std::endl;
        std::cout << "⏰ ВРЕМЯ ВЫШЛО! Игра завершена." << std::endl;
        std::cout << "==========================================" << std::endl;
    }

    map_printer.print_survivors(npcs);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\n==========================================" << std::endl;
        std::cout << "✅ СИМУЛЯЦИЯ ЗАВЕРШЕНА УСПЕШНО!" << std::endl;
        std::cout << "==========================================" << std::endl;
    }

    return 0;
}