#pragma once

#include "entities/Entity.h"
#include <vector>
#include <memory>

namespace RPG {

class Item;
using ItemPtr = std::shared_ptr<Item>;

class Character : public Entity {
public:
    Character(const std::string& name, int hp, int mana, int attack, int defense);

    // Override pure virtual methods
    void takeDamage(int damage) override;
    int dealDamage() const override;
    bool isAlive() const override;
    EntityType getType() const override { return EntityType::PLAYER; }

    // Override virtual methods
    void displayStats() const override;

    // Character-specific methods
    void gainExperience(int xp);
    void levelUp();
    bool canLevelUp() const;
    int getXpForNextLevel() const;

    void addItem(ItemPtr item);
    void removeItem(size_t index);
    void useItem(size_t index);
    void equipWeapon(size_t index);
    void displayInventory() const;

    // Getters
    int getMana() const { return mana; }
    int getMaxMana() const { return maxMana; }
    int getExperience() const { return experience; }
    int getGold() const { return gold; }
    const std::vector<ItemPtr>& getInventory() const { return inventory; }
    ItemPtr getEquippedWeapon() const { return equippedWeapon; }

    // Setters
    void setMana(int value) { mana = value; }
    void addGold(int amount) { gold += amount; }

private:
    int mana;
    int maxMana;
    int experience;
    int gold;
    std::vector<ItemPtr> inventory;
    ItemPtr equippedWeapon;

    void applyLevelUpStats();
};

using CharacterPtr = std::shared_ptr<Character>;

} // namespace RPG
