#include "fight_manager.h"
#include "common.h"
#include <iostream>
#include <chrono>

FightManager::FightManager(std::shared_ptr<Observable> obs) 
    : running(true), observable(obs) {}

FightManager::~FightManager() {
    stop();
}

void FightManager::add_event(std::shared_ptr<NPC> attacker, 
                             std::shared_ptr<NPC> defender) {
    std::lock_guard<std::mutex> lock(mtx);
    events.push({attacker, defender, std::chrono::steady_clock::now()});
    cv.notify_one();
}

void FightManager::process_events(std::atomic<bool>& running_flag) {
    while (running_flag.load()) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::milliseconds(100), 
                   [this]() { return !events.empty() || !running; });
        
        if (!running) break;
        
        if (!events.empty()) {
            FightEvent event = events.front();
            events.pop();
            lock.unlock();
            
            process_single_event(event);
        }
    }
}

void FightManager::process_single_event(const FightEvent& event) {
    // Проверяем, живы ли участники
    if (!event.attacker->is_alive() || !event.defender->is_alive()) {
        return;
    }
    
    // Проверяем по правилам Visitor, может ли атакующий убить защищающегося
    bool can_attack = event.attacker->fight(event.defender);
    
    if (can_attack) {
        // Бросаем кубики для определения исхода боя
        int attack_roll = event.attacker->roll_dice();
        int defense_roll = event.defender->roll_dice();
        
        // Выводим информацию о броске кубиков
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "🎲 Dice roll: " << event.attacker->get_name() 
                      << " rolled " << attack_roll << " vs " 
                      << event.defender->get_name() << " rolled " 
                      << defense_roll << std::endl;
        }
        
        if (attack_roll > defense_roll) {
            event.defender->set_alive(false);
            if (observable) {
                observable->notify(event.attacker, event.defender, true);
            }
        } else {
            if (observable) {
                observable->notify(event.attacker, event.defender, false);
            }
        }
    }
}

void FightManager::stop() {
    running = false;
    cv.notify_all();
}