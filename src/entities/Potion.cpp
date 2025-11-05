#include "entities/Potion.h"
#include "entities/Character.h"
#include "utils/Color.h"
#include <iostream>

namespace RPG {

Potion::Potion(const std::string& name, const std::string& description, int power, PotionType potionType)
    : Item(name, description, ItemType::POTION, power, true), potionType(potionType) {}

void Potion::use(Character& character) {
    switch (potionType) {
        case PotionType::HEALTH:
            character.heal(power);
            std::cout << Color::colorize(character.getName() + " restored " + std::to_string(power) + " HP!",
                                       Color::BRIGHT_GREEN) << "\n";
            break;

        case PotionType::MANA:
            character.setMana(std::min(character.getMana() + power, character.getMaxMana()));
            std::cout << Color::colorize(character.getName() + " restored " + std::to_string(power) + " MP!",
                                       Color::BRIGHT_BLUE) << "\n";
            break;

        case PotionType::FULL_RESTORE:
            character.setHp(character.getMaxHp());
            character.setMana(character.getMaxMana());
            std::cout << Color::colorize(character.getName() + " fully restored!",
                                       Color::BRIGHT_MAGENTA) << "\n";
            break;
    }
}

void Potion::displayInfo() const {
    std::cout << Color::colorize(name, Color::BRIGHT_MAGENTA)
              << " [" << getPotionTypeString() << "] - "
              << Color::colorize("+" + std::to_string(power), Color::BRIGHT_GREEN) << "\n";
    std::cout << "  " << description << "\n";
}

std::string Potion::getPotionTypeString() const {
    switch (potionType) {
        case PotionType::HEALTH: return "Health Potion";
        case PotionType::MANA: return "Mana Potion";
        case PotionType::FULL_RESTORE: return "Full Restore";
        default: return "Unknown";
    }
}

} // namespace RPG
