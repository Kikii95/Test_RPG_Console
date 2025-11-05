#include "entities/Character.h"
#include "entities/Item.h"
#include "core/Config.h"
#include "utils/Color.h"
#include "utils/Random.h"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace RPG {

Character::Character(const std::string& name, int hp, int mana, int attack, int defense)
    : Entity(name, hp, attack, defense, STARTING_LEVEL),
      mana(mana), maxMana(mana), experience(0), gold(0), equippedWeapon(nullptr) {}

void Character::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    hp = std::max(0, hp);

    std::cout << Color::colorize(name, Color::BRIGHT_CYAN) << " takes "
              << Color::colorize(std::to_string(actualDamage), Color::BRIGHT_RED)
              << " damage!\n";
}

int Character::dealDamage() const {
    int baseDamage = attack;

    if (equippedWeapon) {
        baseDamage += equippedWeapon->getPower();
    }

    int variance = Random::getInstance().getInt(-2, 3);
    return std::max(1, baseDamage + variance);
}

bool Character::isAlive() const {
    return hp > 0;
}

void Character::displayStats() const {
    Entity::displayStats();
    std::cout << "  MP: " << Color::colorize(std::to_string(mana) + "/" + std::to_string(maxMana), Color::BRIGHT_MAGENTA) << "\n";
    std::cout << "  XP: " << experience << "/" << getXpForNextLevel() << "\n";
    std::cout << "  Gold: " << Color::colorize(std::to_string(gold), Color::BRIGHT_YELLOW) << "\n";

    if (equippedWeapon) {
        std::cout << "  Weapon: " << Color::colorize(equippedWeapon->getName(), Color::YELLOW)
                  << " (+" << equippedWeapon->getPower() << " ATK)\n";
    }
}

void Character::gainExperience(int xp) {
    experience += xp;
    std::cout << Color::colorize("+" + std::to_string(xp) + " XP", Color::BRIGHT_CYAN) << "\n";

    while (canLevelUp()) {
        levelUp();
    }
}

bool Character::canLevelUp() const {
    return experience >= getXpForNextLevel();
}

int Character::getXpForNextLevel() const {
    return static_cast<int>(BASE_XP_REQUIREMENT * std::pow(XP_SCALING_FACTOR, level - 1));
}

void Character::levelUp() {
    experience -= getXpForNextLevel();
    level++;

    std::cout << "\n" << Color::colorize("★ LEVEL UP! ★", Color::BOLD + Color::BRIGHT_YELLOW) << "\n";
    std::cout << Color::colorize(name, Color::BRIGHT_CYAN) << " is now level " << level << "!\n";

    applyLevelUpStats();
}

void Character::applyLevelUpStats() {
    maxHp += LEVEL_UP_HP_GAIN;
    hp = maxHp;
    maxMana += LEVEL_UP_MANA_GAIN;
    mana = maxMana;
    attack += LEVEL_UP_ATTACK_GAIN;
    defense += LEVEL_UP_DEFENSE_GAIN;

    std::cout << "  HP: " << Color::colorize("+" + std::to_string(LEVEL_UP_HP_GAIN), Color::GREEN) << "\n";
    std::cout << "  MP: " << Color::colorize("+" + std::to_string(LEVEL_UP_MANA_GAIN), Color::GREEN) << "\n";
    std::cout << "  ATK: " << Color::colorize("+" + std::to_string(LEVEL_UP_ATTACK_GAIN), Color::GREEN) << "\n";
    std::cout << "  DEF: " << Color::colorize("+" + std::to_string(LEVEL_UP_DEFENSE_GAIN), Color::GREEN) << "\n";
}

void Character::addItem(ItemPtr item) {
    if (inventory.size() < MAX_INVENTORY_SIZE) {
        inventory.push_back(item);
        std::cout << Color::colorize("Obtained: " + item->getName(), Color::BRIGHT_GREEN) << "\n";
    } else {
        std::cout << Color::colorize("Inventory full!", Color::RED) << "\n";
    }
}

void Character::removeItem(size_t index) {
    if (index < inventory.size()) {
        inventory.erase(inventory.begin() + index);
    }
}

void Character::useItem(size_t index) {
    if (index >= inventory.size()) return;

    ItemPtr item = inventory[index];
    item->use(*this);

    if (item->isConsumable()) {
        removeItem(index);
    }
}

void Character::equipWeapon(size_t index) {
    if (index >= inventory.size()) return;

    ItemPtr item = inventory[index];
    if (item->getItemType() == ItemType::WEAPON) {
        equippedWeapon = item;
        std::cout << Color::colorize("Equipped: " + item->getName(), Color::BRIGHT_GREEN) << "\n";
    }
}

void Character::displayInventory() const {
    if (inventory.empty()) {
        std::cout << Color::colorize("Inventory is empty.", Color::YELLOW) << "\n";
        return;
    }

    std::cout << "\n" << Color::colorize("=== INVENTORY ===", Color::BOLD + Color::BRIGHT_CYAN) << "\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << "[" << i << "] ";
        inventory[i]->displayInfo();
    }
}

} // namespace RPG
