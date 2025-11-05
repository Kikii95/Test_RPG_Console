#pragma once

#include "entities/Item.h"

namespace RPG {

enum class PotionType {
    HEALTH,
    MANA,
    FULL_RESTORE
};

class Potion : public Item {
public:
    Potion(const std::string& name, const std::string& description, int power, PotionType potionType);

    // Override pure virtual methods
    void use(Character& character) override;
    void displayInfo() const override;

    PotionType getPotionType() const { return potionType; }

private:
    PotionType potionType;
    std::string getPotionTypeString() const;
};

using PotionPtr = std::shared_ptr<Potion>;

} // namespace RPG
