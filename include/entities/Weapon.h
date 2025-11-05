#pragma once

#include "entities/Item.h"

namespace RPG {

enum class WeaponType {
    SWORD,
    AXE,
    BOW,
    STAFF
};

class Weapon : public Item {
public:
    Weapon(const std::string& name, const std::string& description, int power, WeaponType weaponType);

    // Override pure virtual methods
    void use(Character& character) override;
    void displayInfo() const override;

    WeaponType getWeaponType() const { return weaponType; }

private:
    WeaponType weaponType;
    std::string getWeaponTypeString() const;
};

using WeaponPtr = std::shared_ptr<Weapon>;

} // namespace RPG
