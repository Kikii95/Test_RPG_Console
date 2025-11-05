#pragma once

#include "entities/Entity.h"

namespace RPG {

class Enemy : public Entity {
public:
    Enemy(const std::string& name, int hp, int attack, int defense, int level,
          EntityType type, int xpReward, int goldReward);

    // Override pure virtual methods
    void takeDamage(int damage) override;
    int dealDamage() const override;
    bool isAlive() const override;
    EntityType getType() const override { return type; }

    // Override virtual methods
    void displayStats() const override;

    // Enemy-specific methods
    int getXpReward() const { return xpReward; }
    int getGoldReward() const { return goldReward; }

private:
    EntityType type;
    int xpReward;
    int goldReward;
};

using EnemyPtr = std::shared_ptr<Enemy>;

} // namespace RPG
