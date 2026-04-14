#include "observer.h"
#include "npc.h"

std::string get_type_string(NpcType type) {
    switch(type) {
        case ElfType: return "Elf";
        case KnightErrantType: return "Knight";
        case DragonType: return "Dragon";
        default: return "Unknown";
    }
}

void ConsoleObserver::on_fight(const std::shared_ptr<NPC> attacker, 
                              const std::shared_ptr<NPC> defender, 
                              bool win) {
    if (win) {
        std::cout << "\n=== KILL ===" << std::endl;
        std::cout << "Attacker: ";
        attacker->print();
        std::cout << "Defender: ";
        defender->print();
    }
}

FileObserver::FileObserver(const std::string& filename) {
    file.open(filename, std::ios::app);
}

FileObserver::~FileObserver() {
    if (file.is_open()) {
        file.close();
    }
}

void FileObserver::on_fight(const std::shared_ptr<NPC> attacker, 
                           const std::shared_ptr<NPC> defender, 
                           bool win) {
    if (!file.is_open()) return;

    std::string attacker_name = get_type_string(attacker->type);
    std::string defender_name = get_type_string(defender->type);
    
    file << attacker_name << " at (" << attacker->x << "," << attacker->y << ") ";
    file << (win ? "defeated" : "lost to") << " ";
    file << defender_name << " at (" << defender->x << "," << defender->y << ")";
    file << std::endl;
}