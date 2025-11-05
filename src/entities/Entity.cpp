#include "entities/Entity.h"
#include "utils/Color.h"
#include <iostream>
#include <algorithm>

namespace RPG {

Entity::Entity(const std::string& name, int hp, int attack, int defense, int level)
    : name(name), hp(hp), maxHp(hp), attack(attack), defense(defense), level(level) {}

void Entity::displayStats() const {
    std::cout << Color::colorize(name, Color::BOLD) << " [Lvl " << level << "]\n";
    std::cout << "  HP: " << Color::colorize(std::to_string(hp) + "/" + std::to_string(maxHp), Color::BRIGHT_GREEN) << "\n";
    std::cout << "  ATK: " << Color::colorize(std::to_string(attack), Color::BRIGHT_RED) << " ";
    std::cout << "DEF: " << Color::colorize(std::to_string(defense), Color::BRIGHT_BLUE) << "\n";
}

void Entity::heal(int amount) {
    hp = std::min(hp + amount, maxHp);
}

} // namespace RPG
