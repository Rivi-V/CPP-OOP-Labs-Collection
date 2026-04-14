#include "helpers.h"

std::string type_to_string(NpcType type) {
    switch (type) {
        case NpcType::DragonType: return "Dragon";
        case NpcType::ElfType: return "Elf";
        case NpcType::KnightType: return "Knight";
        default: return "Unknown";
    }
}