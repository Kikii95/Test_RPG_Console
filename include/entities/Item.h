#pragma once

#include <string>
#include <memory>

namespace RPG {

class Character;

enum class ItemType {
    WEAPON,
    POTION,
    CONSUMABLE
};

class Item {
public:
    Item(const std::string& name, const std::string& description, ItemType type, int power, bool consumable);
    virtual ~Item() = default;

    // Pure virtual methods
    virtual void use(Character& character) = 0;
    virtual void displayInfo() const = 0;

    // Getters
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    ItemType getItemType() const { return type; }
    int getPower() const { return power; }
    bool isConsumable() const { return consumable; }

protected:
    std::string name;
    std::string description;
    ItemType type;
    int power;
    bool consumable;
};

using ItemPtr = std::shared_ptr<Item>;

} // namespace RPG
