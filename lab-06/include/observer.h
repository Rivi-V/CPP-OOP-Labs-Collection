#pragma once
#include <memory>
#include <iostream>
#include <fstream>

struct NPC;

class IFightObserver {
public:
    virtual void on_fight(const std::shared_ptr<NPC> attacker, 
                         const std::shared_ptr<NPC> defender, 
                         bool win) = 0; // в сражении
    virtual ~IFightObserver() = default; 
};

class ConsoleObserver : public IFightObserver {
public:
    void on_fight(const std::shared_ptr<NPC> attacker, 
                 const std::shared_ptr<NPC> defender, 
                 bool win) override; // консольный наблюдатель выводит информацию о боях в консоль
};

class FileObserver : public IFightObserver { 
private:
    std::ofstream file;
public:
    FileObserver(const std::string& filename);
    ~FileObserver();
    void on_fight(const std::shared_ptr<NPC> attacker, 
                 const std::shared_ptr<NPC> defender, 
                 bool win) override;
}; // файловый наблюдатель выводит в файл