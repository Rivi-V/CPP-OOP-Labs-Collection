#include "factory.h"
#include <fstream>
#include <sstream>
#include "visitor.h"

std::shared_ptr<NPC> factory(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) { // если нам из потока дали какой-то тип
        switch (type) {
        case ElfType:
            result = std::make_shared<Elf>(is); // создаём умный указатель (объект + счётчик ссылок)
            break;
        case KnightErrantType:
            result = std::make_shared<KnightErrant>(is);
            break;
        case DragonType:
            result = std::make_shared<Dragon>(is);
            break;
        }
    }
    
    if (result) {
        // Подписываем на наблюдателей
        static auto console_observer = std::make_shared<ConsoleObserver>();
        // static - создаётся один раз при первом вызове factory()
        // auto - автоматическое определение типа
        static auto file_observer = std::make_shared<FileObserver>("log.txt");
        result->subscribe(console_observer); // подписываем их
        result->subscribe(file_observer);
    }
    
    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
    case ElfType:
        result = std::make_shared<Elf>(x, y); 
        break;
    case KnightErrantType:
        result = std::make_shared<KnightErrant>(x, y);
        break;
    case DragonType:
        result = std::make_shared<Dragon>(x, y);
        break;
    default:
        break;
    }
    
    if (result) {
        // Подписываем на наблюдателей
        static auto console_observer = std::make_shared<ConsoleObserver>();
        static auto file_observer = std::make_shared<FileObserver>("log.txt");
        result->subscribe(console_observer);
        result->subscribe(file_observer);
    }
    
    return result;
}

void save(const set_t &array, const std::string &filename) {
    // Открываем файл для записи
    std::ofstream fs(filename);
    // Записываем КОЛИЧЕСТВО NPC в первой строке
    fs << array.size() << std::endl;
    // Для каждого NPC вызываем его метод save()
    for (auto &n : array) { //  n это ССЫЛКА на shared_ptr
        n->save(fs);
    }
    fs.close();
}

set_t load(const std::string &filename) {
    set_t result; // множество std::set<std::shared_ptr<NPC>>
    std::ifstream is(filename); // открываем filename в поток вывода из файла
    if (is.good() && is.is_open()) {
    // is.good() - проверяет, что поток в "хорошем" состоянии (нет ошибок)
    // is.is_open() - проверяет, что файл действительно открыт
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) {
            result.insert(factory(is)); // добавляет созданного NPC в множество result
        }
        is.close();
    }
    return result;
}

// Функция боя с использованием Visitor паттерна
set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;
    ConcreteFightVisitor visitor;

    for (const auto &attacker : array) {
        if (!attacker->is_alive()) continue;
        
        for (const auto &defender : array) {
            if (attacker == defender || !defender->is_alive()) continue;
            
            if (attacker->is_close(defender, distance)) {
                // используем паттерн посетитель
                bool success = defender->accept(attacker);
                if (success) {
                    defender->set_alive(false);
                    dead_list.insert(defender);
                    // а тут потерн наблюдатель
                    attacker->fight_notify(defender, true);
                }
            }
        }
    }
    
    return dead_list;
}