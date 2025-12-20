#include "factory.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include <sstream>
#include <iostream>

// Значения по умолчанию из таблицы для варианта 2
constexpr int DEFAULT_DRAGON_MOVE = 50;
constexpr int DEFAULT_DRAGON_KILL = 30;
constexpr int DEFAULT_ELF_MOVE = 10;
constexpr int DEFAULT_ELF_KILL = 50;
constexpr int DEFAULT_KNIGHT_MOVE = 30;
constexpr int DEFAULT_KNIGHT_KILL = 10;

std::shared_ptr<NPC> Factory::create(NpcType type, int x, int y, 
                                     const std::string& name,
                                     int move_distance, 
                                     int kill_distance) {
    // Если параметры не указаны, используем значения по умолчанию
    switch (type) {
        case NpcType::DragonType:
            if (move_distance == -1) move_distance = DEFAULT_DRAGON_MOVE;
            if (kill_distance == -1) kill_distance = DEFAULT_DRAGON_KILL;
            return std::make_shared<Dragon>(x, y, name, move_distance, kill_distance);
            
        case NpcType::ElfType:
            if (move_distance == -1) move_distance = DEFAULT_ELF_MOVE;
            if (kill_distance == -1) kill_distance = DEFAULT_ELF_KILL;
            return std::make_shared<Elf>(x, y, name, move_distance, kill_distance);
            
        case NpcType::KnightType:
            if (move_distance == -1) move_distance = DEFAULT_KNIGHT_MOVE;
            if (kill_distance == -1) kill_distance = DEFAULT_KNIGHT_KILL;
            return std::make_shared<KnightErrant>(x, y, name, 50, 30, move_distance, kill_distance);
            
        default:
            throw std::runtime_error("Unknown NPC type");
    }
}

std::shared_ptr<NPC> Factory::load(std::istream& is) {
    std::string type_str;
    
    if (!(is >> type_str)) {
        throw std::runtime_error("Failed to read NPC type");
    }
    
    int x, y;
    std::string name;
    
    if (!(is >> x >> y >> name)) {
        throw std::runtime_error("Failed to read NPC data");
    }
    
    // Для совместимости с сохраненными файлами из лабы 6
    // Сначала пробуем прочитать только основные параметры
    if (type_str == "Dragon") {
        int move_dist = DEFAULT_DRAGON_MOVE;
        int kill_dist = DEFAULT_DRAGON_KILL;
        
        // Пробуем прочитать дополнительные параметры
        std::streampos pos = is.tellg();
        if (is >> move_dist >> kill_dist) {
            // Успешно прочитали оба параметра
        } else {
            // Возвращаемся назад и используем значения по умолчанию
            is.clear();
            is.seekg(pos);
        }
        
        return std::make_shared<Dragon>(x, y, name, move_dist, kill_dist);
    } 
    else if (type_str == "Elf") {
        int move_dist = DEFAULT_ELF_MOVE;
        int kill_dist = DEFAULT_ELF_KILL;
        
        std::streampos pos = is.tellg();
        if (is >> move_dist >> kill_dist) {
        } else {
            is.clear();
            is.seekg(pos);
        }
        
        return std::make_shared<Elf>(x, y, name, move_dist, kill_dist);
    } 
    else if (type_str == "Knight") {
        // У рыцаря больше параметров
        int armor = 50, sword_power = 30;
        int move_dist = DEFAULT_KNIGHT_MOVE;
        int kill_dist = DEFAULT_KNIGHT_KILL;
        
        // Пытаемся прочитать все параметры
        std::streampos pos = is.tellg();
        if (is >> armor >> sword_power >> move_dist >> kill_dist) {
            // Успешно прочитали все 4 параметра
        } else {
            // Возвращаемся и пробуем прочитать только броню и силу меча
            is.clear();
            is.seekg(pos);
            if (is >> armor >> sword_power) {
                // Только броня и сила меча
            } else {
                // Только значения по умолчанию
                is.clear();
                is.seekg(pos);
            }
        }
        
        return std::make_shared<KnightErrant>(x, y, name, armor, sword_power, move_dist, kill_dist);
    }
    else {
        throw std::runtime_error("Unknown NPC type in file: " + type_str);
    }
}
