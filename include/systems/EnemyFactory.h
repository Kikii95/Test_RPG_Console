#pragma once

#include "entities/Enemy.h"
#include <vector>
#include <string>

namespace RPG {

struct EnemyTemplate {
    std::string name;
    int baseHp;
    int baseAttack;
    int baseDefense;
    EntityType type;
    int xpReward;
    int goldReward;
};

class EnemyFactory {
public:
    static EnemyPtr createRandomEnemy(int playerLevel);
    static EnemyPtr createBoss(int playerLevel);

private:
    static std::vector<EnemyTemplate> getEnemyTemplates();
    static EnemyPtr createFromTemplate(const EnemyTemplate& tmpl, int level);
};

} // namespace RPG
