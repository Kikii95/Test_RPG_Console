#pragma once

#include "entities/Character.h"
#include "entities/Enemy.h"
#include <memory>

namespace RPG {

enum class CombatAction {
    ATTACK,
    USE_ITEM,
    RUN
};

class CombatSystem {
public:
    static bool startBattle(CharacterPtr player, EnemyPtr enemy);

private:
    static CombatAction getPlayerAction(CharacterPtr player);
    static void executePlayerTurn(CharacterPtr player, EnemyPtr enemy, CombatAction action);
    static void executeEnemyTurn(CharacterPtr player, EnemyPtr enemy);
    static void displayBattleStatus(CharacterPtr player, EnemyPtr enemy);
    static void rewardPlayer(CharacterPtr player, EnemyPtr enemy);
};

} // namespace RPG
