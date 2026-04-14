#include "npc.h"
#include "visitor.h"
#include "battle_visitor.h"
#include <cmath>
#include <iostream>
#include <random>
#include <shared_mutex>  // ДОБАВЬТЕ!

NPC::NPC(NpcType t, int x, int y, const std::string& name,
         int move_dist, int kill_dist)
    : type(t), x(x), y(y), name(name), alive(true),
      move_distance(move_dist), kill_distance(kill_dist) {}

NpcType NPC::get_type() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return type;
}

int NPC::get_x() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return x;
}

int NPC::get_y() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return y;
}

std::string NPC::get_name() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return name;
}

bool NPC::is_alive() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return alive;
}

int NPC::get_move_distance() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return move_distance;
}

int NPC::get_kill_distance() const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return kill_distance;
}

void NPC::set_alive(bool status) {
    std::lock_guard<std::shared_mutex> lock(mtx);
    alive = status;
}

void NPC::move(int max_x, int max_y) {
    std::lock_guard<std::shared_mutex> lock(mtx);
    if (!alive) return;
    
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-move_distance, move_distance);
    
    int dx = dist(gen);
    int dy = dist(gen);
    
    x = std::max(0, std::min(max_x - 1, x + dx));
    y = std::max(0, std::min(max_y - 1, y + dy));
}

double NPC::distance(const std::shared_ptr<NPC>& other) const {
    std::shared_lock<std::shared_mutex> lock1(mtx, std::defer_lock);
    std::shared_lock<std::shared_mutex> lock2(other->mtx, std::defer_lock);
    std::lock(lock1, lock2);
    
    int dx = x - other->x;
    int dy = y - other->y;
    return std::sqrt(dx*dx + dy*dy);
}

bool NPC::is_close(const std::shared_ptr<NPC>& other) const {
    std::shared_lock<std::shared_mutex> lock1(mtx, std::defer_lock);
    std::shared_lock<std::shared_mutex> lock2(other->mtx, std::defer_lock);
    std::lock(lock1, lock2);
    
    if (!alive || !other->alive) return false;
    if (this == other.get()) return false;
    
    int dx = x - other->x;
    int dy = y - other->y;
    double dist = std::sqrt(dx*dx + dy*dy);
    return dist <= kill_distance;
}

bool NPC::fight(std::shared_ptr<NPC> defender) {
    auto visitor = std::make_shared<BattleVisitor>(this->get_type(), this->get_name());
    return defender->accept(visitor);
}

int NPC::roll_dice() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
}