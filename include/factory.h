#pragma once
#include "npc.h"
#include "dragon.h"
#include "elf.h"
#include "knight_errant.h"
#include "observer.h"

std::shared_ptr<NPC> factory(std::istream &is); // фабричная функция создаёт npc из потока данных
std::shared_ptr<NPC> factory(NpcType type, int x, int y); // фабричная функция создаёт npc по типу и координатам
void save(const set_t &array, const std::string &filename); // Сохраняет все NPC из множества в файл
set_t load(const std::string &filename); // загружает NPC из файла в множество
set_t fight(const set_t &array, size_t distance); // проводит бой