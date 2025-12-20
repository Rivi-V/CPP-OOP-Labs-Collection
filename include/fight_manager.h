#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include "npc.h"
#include "observer.h"

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
    std::chrono::steady_clock::time_point timestamp;
};

class FightManager {
private:
    std::queue<FightEvent> events;
    mutable std::mutex mtx;
    std::condition_variable cv;
    bool running;
    std::shared_ptr<Observable> observable;
    
public:
    FightManager(std::shared_ptr<Observable> obs);
    ~FightManager();
    
    void add_event(std::shared_ptr<NPC> attacker, 
                   std::shared_ptr<NPC> defender);
    
    void process_events(std::atomic<bool>& running_flag);
    void stop();
    
private:
    void process_single_event(const FightEvent& event);
};