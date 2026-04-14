#pragma once
#include <memory>
#include <string>
#include <istream>
#include "npc_type.h"

class NPC;

class Factory {
public:
    // Создание NPC с параметрами движения
    static std::shared_ptr<NPC> create(NpcType type, int x, int y, 
                                       const std::string& name,
                                       int move_distance = -1, 
                                       int kill_distance = -1);
    
    // Загрузка NPC из потока (с поддержкой дополнительных параметров)
    static std::shared_ptr<NPC> load(std::istream& is);
};