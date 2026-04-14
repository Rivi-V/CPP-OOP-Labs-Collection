#pragma once // Защита от многократного включения

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <math.h>
#include "observer.h"

struct NPC; // Предварительное объявление. Подготавливает систему для реализации паттерна "Посетитель" или фабрики NPC
struct Elf;
struct KnightErrant;
struct Dragon;
using set_t = std::set<std::shared_ptr<NPC>>; // Тип для хранения NPC

enum NpcType {
    Unknown = 0,
    ElfType = 1,
    KnightErrantType = 2,
    DragonType = 3
};

struct NPC : public std::enable_shared_from_this<NPC> { // Класс наследуется от enable_shared_from_this для безопасного получения shared_ptr на текущий объект.
    NpcType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<IFightObserver>> observers; // список наблюдателей за боями

    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is); // Создание из потока (для загрузки)

    void subscribe(std::shared_ptr<IFightObserver> observer);  // Подписка на события
    void fight_notify(const std::shared_ptr<NPC> defender, bool win); // Уведомление наблюдателей кто победил
    
    bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const; // Проверяет, находится ли другой NPC в пределах заданной дистанции
    bool is_alive() const; // Проверка жив ли NPC
    void set_alive(bool status); // Изменение состояния
    
    virtual bool accept(const std::shared_ptr<NPC>& attacker) = 0; // Метод "принятия посетителя" - определяет логику боя
    virtual void print() = 0; // Вывод информации о NPC
    virtual void save(std::ostream &os); // Сохранение состояния в поток

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);

protected:
    bool alive{true}; // жив / нет
};