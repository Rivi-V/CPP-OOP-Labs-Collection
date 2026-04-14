#pragma once
#include <memory>
#include <vector>
#include <string>
#include <mutex>

class NPC;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void on_fight(const std::shared_ptr<NPC>& attacker, 
                         const std::shared_ptr<NPC>& defender, 
                         bool win) = 0;
};

class ConsoleObserver : public Observer {
public:
    void on_fight(const std::shared_ptr<NPC>& attacker,
                 const std::shared_ptr<NPC>& defender,
                 bool win) override;
};

class FileObserver : public Observer {
private:
    std::string filename;
    std::mutex file_mutex;
public:
    FileObserver(const std::string& filename);
    void on_fight(const std::shared_ptr<NPC>& attacker,
                 const std::shared_ptr<NPC>& defender,
                 bool win) override;
};

class Observable {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void add_observer(std::shared_ptr<Observer> observer);
    void notify(const std::shared_ptr<NPC>& attacker,
                const std::shared_ptr<NPC>& defender,
                bool win);
};