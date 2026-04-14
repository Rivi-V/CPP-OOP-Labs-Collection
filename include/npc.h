#pragma once
#include <memory>
#include <string>
#include <mutex>
#include <shared_mutex>  // ДОБАВЬТЕ!
#include <random>
#include "npc_type.h"
#include "visitor.h"

class NPC {
protected:
    NpcType type;
    int x, y;
    std::string name;
    bool alive;
    int move_distance;    // Расстояние хода
    int kill_distance;    // Расстояние убийства
    mutable std::shared_mutex mtx;  // ИЗМЕНИТЕ на shared_mutex!
    
public:
    NPC(NpcType t, int x, int y, const std::string& name, 
        int move_dist, int kill_dist);
    virtual ~NPC() = default;
    
    virtual bool accept(std::shared_ptr<Visitor> visitor) = 0;
    virtual void print() const = 0;
    virtual void save(std::ostream& os) const = 0;
    
    // Геттеры с блокировкой
    NpcType get_type() const;
    int get_x() const;
    int get_y() const;
    std::string get_name() const;
    bool is_alive() const;
    int get_move_distance() const;
    int get_kill_distance() const;
    
    // Безопасные методы
    void set_alive(bool status);
    void move(int max_x, int max_y);
    double distance(const std::shared_ptr<NPC>& other) const;
    bool is_close(const std::shared_ptr<NPC>& other) const;
    
    // Бой через Visitor
    bool fight(std::shared_ptr<NPC> defender);
    
    // Кубик для боя
    static int roll_dice();
};