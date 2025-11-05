#include "entities/Enemy.h"
#include "utils/Color.h"
#include "utils/Random.h"
#include <iostream>
#include <algorithm>

namespace RPG {

Enemy::Enemy(const std::string& name, int hp, int attack, int defense, int level,
             EntityType type, int xpReward, int goldReward)
    : Entity(name, hp, attack, defense, level),
      type(type), xpReward(xpReward), goldReward(goldReward) {}

void Enemy::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    hp = std::max(0, hp);

    std::cout << Color::colorize(name, Color::BRIGHT_RED) << " takes "
              << Color::colorize(std::to_string(actualDamage), Color::BRIGHT_YELLOW)
              << " damage!\n";
}

int Enemy::dealDamage() const {
    int variance = Random::getInstance().getInt(-1, 2);
    return std::max(1, attack + variance);
}

bool Enemy::isAlive() const {
    return hp > 0;
}

void Enemy::displayStats() const {
    std::string typeStr;
    std::string color;

    switch (type) {
        case EntityType::ENEMY_WEAK:
            typeStr = "Weak";
            color = Color::GREEN;
            break;
        case EntityType::ENEMY_NORMAL:
            typeStr = "Normal";
            color = Color::YELLOW;
            break;
        case EntityType::ENEMY_STRONG:
            typeStr = "Strong";
            color = Color::RED;
            break;
        case EntityType::ENEMY_BOSS:
            typeStr = "BOSS";
            color = Color::BRIGHT_MAGENTA;
            break;
        default:
            typeStr = "Unknown";
            color = Color::WHITE;
    }

    std::cout << Color::colorize(name, color + Color::BOLD)
              << " [" << typeStr << " - Lvl " << level << "]\n";
    std::cout << "  HP: " << Color::colorize(std::to_string(hp) + "/" + std::to_string(maxHp), Color::BRIGHT_GREEN) << "\n";
    std::cout << "  ATK: " << Color::colorize(std::to_string(attack), Color::BRIGHT_RED) << " ";
    std::cout << "DEF: " << Color::colorize(std::to_string(defense), Color::BRIGHT_BLUE) << "\n";
}

} // namespace RPG
