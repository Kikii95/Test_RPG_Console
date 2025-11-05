#include "entities/Weapon.h"
#include "entities/Character.h"
#include "utils/Color.h"
#include <iostream>

namespace RPG {

Weapon::Weapon(const std::string& name, const std::string& description, int power, WeaponType weaponType)
    : Item(name, description, ItemType::WEAPON, power, false), weaponType(weaponType) {}

void Weapon::use(Character& character) {
    std::cout << Color::colorize("Equipped " + name, Color::BRIGHT_GREEN) << "\n";
}

void Weapon::displayInfo() const {
    std::cout << Color::colorize(name, Color::BRIGHT_YELLOW)
              << " [" << getWeaponTypeString() << "] - "
              << Color::colorize("+" + std::to_string(power) + " ATK", Color::BRIGHT_RED) << "\n";
    std::cout << "  " << description << "\n";
}

std::string Weapon::getWeaponTypeString() const {
    switch (weaponType) {
        case WeaponType::SWORD: return "Sword";
        case WeaponType::AXE: return "Axe";
        case WeaponType::BOW: return "Bow";
        case WeaponType::STAFF: return "Staff";
        default: return "Unknown";
    }
}

} // namespace RPG
