#include "npc.h"

NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t) {
    is >> x >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &o : observers) {
        o->on_fight(shared_from_this(), defender, win); 
        // shared_from_this(): безопасно создает shared_ptr на текущий объект
    }
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const { // определяет дистанцию
    int dx = x - other->x;
    int dy = y - other->y;
    return std::sqrt(dx*dx + dy*dy) <= distance;
}

bool NPC::is_alive() const {
    return alive;
}

void NPC::set_alive(bool status) {
    alive = status;
}

void NPC::save(std::ostream &os) { // сохранения в поток
    os << x << " " << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}