#include "observer.h"
#include "npc.h"
#include "common.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "helpers.h"  // для type_to_string

// ==================== ConsoleObserver ====================

void ConsoleObserver::on_fight(const std::shared_ptr<NPC>& attacker,
                              const std::shared_ptr<NPC>& defender,
                              bool win) {
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    
    std::lock_guard<std::mutex> lock(cout_mutex);
    
    std::cout << "[" << buffer << "] ";
    
    if (win) {
        std::cout << attacker->get_name() << " [" 
                  << type_to_string(attacker->get_type())
                  << "] killed " 
                  << defender->get_name() << " [" 
                  << type_to_string(defender->get_type()) 
                  << "]" << std::endl;
    } else {
        std::cout << attacker->get_name() << " [" 
                  << type_to_string(attacker->get_type()) 
                  << "] failed to kill " 
                  << defender->get_name() << " [" 
                  << type_to_string(defender->get_type()) 
                  << "]" << std::endl;
    }
}

// ==================== FileObserver ====================

FileObserver::FileObserver(const std::string& filename) : filename(filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (file.is_open()) {
        file << "=== Battle Log ===\n";
        file.close();
    }
}

void FileObserver::on_fight(const std::shared_ptr<NPC>& attacker,
                           const std::shared_ptr<NPC>& defender,
                           bool win) {
    std::lock_guard<std::mutex> lock(file_mutex);
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open log file " << filename << std::endl;
        return;
    }
    
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    
    file << "[" << buffer << "] ";
    
    if (win) {
        file << attacker->get_name() << " [" 
             << type_to_string(attacker->get_type()) 
             << "] killed " 
             << defender->get_name() << " [" 
             << type_to_string(defender->get_type()) 
             << "] at (" << defender->get_x() << ", " 
             << defender->get_y() << ")\n";
    } else {
        file << attacker->get_name() << " [" 
             << type_to_string(attacker->get_type()) 
             << "] failed to kill " 
             << defender->get_name() << " [" 
             << type_to_string(defender->get_type()) 
             << "]\n";
    }
    
    file.close();
}

// ==================== Observable ====================

void Observable::add_observer(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Observable::notify(const std::shared_ptr<NPC>& attacker,
                       const std::shared_ptr<NPC>& defender,
                       bool win) {
    for (auto& observer : observers) {
        observer->on_fight(attacker, defender, win);
    }
}