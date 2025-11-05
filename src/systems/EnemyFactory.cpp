#include "systems/EnemyFactory.h"
#include "utils/Random.h"

namespace RPG {

std::vector<EnemyTemplate> EnemyFactory::getEnemyTemplates() {
    return {
        {"Goblin", 30, 8, 2, EntityType::ENEMY_WEAK, 20, 10},
        {"Skeleton", 40, 10, 3, EntityType::ENEMY_WEAK, 25, 15},
        {"Orc Warrior", 60, 15, 5, EntityType::ENEMY_NORMAL, 40, 25},
        {"Dark Knight", 80, 20, 8, EntityType::ENEMY_NORMAL, 60, 40},
        {"Troll Berserker", 100, 25, 10, EntityType::ENEMY_STRONG, 100, 60},
        {"Shadow Assassin", 70, 30, 6, EntityType::ENEMY_STRONG, 90, 55},
        {"Ancient Dragon", 200, 40, 15, EntityType::ENEMY_BOSS, 300, 150},
        {"Demon Lord", 250, 50, 20, EntityType::ENEMY_BOSS, 500, 250}
    };
}

EnemyPtr EnemyFactory::createRandomEnemy(int playerLevel) {
    auto templates = getEnemyTemplates();
    std::vector<EnemyTemplate> suitableEnemies;

    for (const auto& tmpl : templates) {
        if (tmpl.type != EntityType::ENEMY_BOSS) {
            suitableEnemies.push_back(tmpl);
        }
    }

    int index = Random::getInstance().getInt(0, suitableEnemies.size() - 1);
    int enemyLevel = std::max(1, playerLevel + Random::getInstance().getInt(-1, 2));

    return createFromTemplate(suitableEnemies[index], enemyLevel);
}

EnemyPtr EnemyFactory::createBoss(int playerLevel) {
    auto templates = getEnemyTemplates();
    std::vector<EnemyTemplate> bosses;

    for (const auto& tmpl : templates) {
        if (tmpl.type == EntityType::ENEMY_BOSS) {
            bosses.push_back(tmpl);
        }
    }

    int index = Random::getInstance().getInt(0, bosses.size() - 1);
    return createFromTemplate(bosses[index], playerLevel + 3);
}

EnemyPtr EnemyFactory::createFromTemplate(const EnemyTemplate& tmpl, int level) {
    float levelMultiplier = 1.0f + (level - 1) * 0.2f;

    int hp = static_cast<int>(tmpl.baseHp * levelMultiplier);
    int attack = static_cast<int>(tmpl.baseAttack * levelMultiplier);
    int defense = static_cast<int>(tmpl.baseDefense * levelMultiplier);
    int xp = static_cast<int>(tmpl.xpReward * levelMultiplier);
    int gold = static_cast<int>(tmpl.goldReward * levelMultiplier);

    return std::make_shared<Enemy>(tmpl.name, hp, attack, defense, level, tmpl.type, xp, gold);
}

} // namespace RPG
