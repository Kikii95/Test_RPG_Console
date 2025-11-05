#include "entities/Item.h"

namespace RPG {

Item::Item(const std::string& name, const std::string& description, ItemType type, int power, bool consumable)
    : name(name), description(description), type(type), power(power), consumable(consumable) {}

} // namespace RPG
