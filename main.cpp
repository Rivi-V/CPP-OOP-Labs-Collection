#include "npc.h"
#include "dragon.h"
#include "knight_errant.h"
#include "elf.h"
#include "concrete_fight_visitor.h"

class ConsoleObserver : public IFightObserver
{
private:
    ConsoleObserver(){};

public:
    static std::shared_ptr<IFightObserver> get()
    {
        static ConsoleObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override
    {
        if (win)
        {
            std::cout << "⚔️  " << get_type_emoji(attacker->type) << " " 
                      << get_type_name(attacker->type)
                      << " победил " << get_type_emoji(defender->type) << " " 
                      << get_type_name(defender->type)
                      << " [" << attacker->x << "," << attacker->y << "] → [" 
                      << defender->x << "," << defender->y << "]" << std::endl;
        }
    }

private:
    std::string get_type_emoji(NpcType type) {
        switch(type) {
            case DragonType: return "🐉";
            case ElfType: return "🧝";
            case KnightErrantType: return "🛡️";
            default: return "❓";
        }
    }

    std::string get_type_name(NpcType type) {
        switch(type) {
            case DragonType: return "Дракон";
            case ElfType: return "Эльф";
            case KnightErrantType: return "Рыцарь";
            default: return "Неизвестный";
        }
    }
};

std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type)
    {
        switch (type)
        {
        case ElfType:
            result = std::make_shared<Elf>(is);
            break;
        case KnightErrantType:
            result = std::make_shared<KnightErrant>(is);
            break;
        case DragonType:
            result = std::make_shared<Dragon>(is);
            break;
        }
    }
    else
        std::cerr << "❌ Неожиданный тип NPC: " << type << std::endl;

    if (result)
        result->subscribe(ConsoleObserver::get());

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y)
{
    std::shared_ptr<NPC> result;
    switch (type)
    {
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
    if (result)
        result->subscribe(ConsoleObserver::get());

    return result;
}


void save(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename)
{
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is));
        is.close();
    }
    else
        std::cerr << "❌ Ошибка загрузки: " << std::strerror(errno) << std::endl;
    return result;
}

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}

void print_npc_stats(const set_t& array) {
    int dragons = 0, elves = 0, knights = 0;
    
    for (const auto& npc : array) {
        switch(npc->type) {
            case DragonType: dragons++; break;
            case ElfType: elves++; break;
            case KnightErrantType: knights++; break;
            default: break;
        }
    }
    
    std::cout << "📊 Статистика: 🐉 Драконы: " << dragons 
              << " | 🧝 Эльфы: " << elves 
              << " | 🛡️ Рыцари: " << knights 
              << " | Всего: " << array.size() << std::endl;
}

set_t fight(const set_t &array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) && 
                attacker->isAlive() && defender->isAlive() &&
                attacker->is_close(defender, distance))
            {
                bool success = defender->accept(attacker);
                if (success) {
                    defender->setAlive(false);
                    dead_list.insert(defender);
                    attacker->fight_notify(defender, true);
                }
            }

    return dead_list;
}

int main()
{
    std::cout << "🎮 ===== РЕДАКТОР ПОДЗЕМЕЛЬЯ BALAGUR FATE 3 =====" << std::endl;
    std::cout << "🎯 Вариант 2: Дракон, Эльф, Странствующий рыцарь" << std::endl;
    std::cout << "=============================================" << std::endl;

    set_t array;

    std::cout << std::endl << "🔮 Генерируем NPC..." << std::endl;
    for (size_t i = 0; i < 10; ++i) {
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                           std::rand() % 100,
                           std::rand() % 100));
    }
    
    std::cout << "✅ Сгенерировано NPC: " << array.size() << std::endl;
    print_npc_stats(array);

    std::cout << std::endl << "💾 Сохраняем в файл..." << std::endl;
    save(array, "npc.txt");
    std::cout << "✅ Сохранено в npc.txt" << std::endl;

    std::cout << std::endl << "📂 Загружаем из файла..." << std::endl;
    array = load("npc.txt");
    std::cout << "✅ Загружено NPC: " << array.size() << std::endl;

    std::cout << std::endl << "⚔️  ===== НАЧАЛО БОЕВ =====" << std::endl;
    print_npc_stats(array);

    int round = 1;
    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10, round++)
    {
        std::cout << std::endl << "🎯 РАУНД " << round << " (дистанция: " << distance << "м)" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        auto dead_list = fight(array, distance);
        
        if (!dead_list.empty()) {
            std::cout << "💀 Убито в этом раунде: " << dead_list.size() << std::endl;
        } else {
            std::cout << "✅ В этом раунде никто не погиб" << std::endl;
        }
        
        for (auto &d : dead_list)
            array.erase(d);
            
        std::cout << "👥 Выжило: " << array.size() << std::endl;
        print_npc_stats(array);

        if (array.size() <= 1) break;
    }

    std::cout << std::endl << "🏆 ===== ФИНАЛЬНЫЕ РЕЗУЛЬТАТЫ =====" << std::endl;
    
    if (array.empty()) {
        std::cout << "💀 Все NPC погибли в бою!" << std::endl;
    } else if (array.size() == 1) {
        std::cout << "👑 ПОБЕДИТЕЛЬ:" << std::endl;
        auto winner = *array.begin();
        std::string type_name;
        std::string emoji;
        
        switch(winner->type) {
            case DragonType: type_name = "Дракон"; emoji = "🐉"; break;
            case ElfType: type_name = "Эльф"; emoji = "🧝"; break;
            case KnightErrantType: type_name = "Рыцарь"; emoji = "🛡️"; break;
            default: type_name = "Неизвестный"; emoji = "❓";
        }
        
        std::cout << emoji << " " << type_name 
                  << " на позиции [" << winner->x << "," << winner->y << "]" << std::endl;
    } else {
        std::cout << "🤝 В живых осталось несколько NPC:" << std::endl;
        for (auto &npc : array) {
            npc->print();
        }
    }

    std::cout << std::endl << "🎉 Симуляция завершена!" << std::endl;
    return 0;
}