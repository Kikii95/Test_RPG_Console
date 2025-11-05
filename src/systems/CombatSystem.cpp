#include "systems/CombatSystem.h"
#include "utils/Color.h"
#include "utils/Random.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace RPG {

bool CombatSystem::startBattle(CharacterPtr player, EnemyPtr enemy) {
    std::cout << "\n" << Color::colorize("╔═══════════════════════════════════╗", Color::BRIGHT_RED) << "\n";
    std::cout << Color::colorize("║       ⚔️  BATTLE START!  ⚔️       ║", Color::BOLD + Color::BRIGHT_RED) << "\n";
    std::cout << Color::colorize("╚═══════════════════════════════════╝", Color::BRIGHT_RED) << "\n\n";

    std::cout << Color::colorize(player->getName(), Color::BRIGHT_CYAN) << " encounters "
              << Color::colorize(enemy->getName(), Color::BRIGHT_RED) << "!\n\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    while (player->isAlive() && enemy->isAlive()) {
        displayBattleStatus(player, enemy);

        CombatAction action = getPlayerAction(player);

        if (action == CombatAction::RUN) {
            if (Random::getInstance().chance(0.5f)) {
                std::cout << Color::colorize("Successfully escaped!", Color::BRIGHT_GREEN) << "\n";
                return false;
            } else {
                std::cout << Color::colorize("Can't escape!", Color::RED) << "\n";
            }
        } else {
            executePlayerTurn(player, enemy, action);
        }

        if (enemy->isAlive()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            executeEnemyTurn(player, enemy);
        }

        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    if (player->isAlive()) {
        std::cout << Color::colorize("╔═══════════════════════════════════╗", Color::BRIGHT_GREEN) << "\n";
        std::cout << Color::colorize("║         🏆 VICTORY! 🏆           ║", Color::BOLD + Color::BRIGHT_GREEN) << "\n";
        std::cout << Color::colorize("╚═══════════════════════════════════╝", Color::BRIGHT_GREEN) << "\n\n";
        rewardPlayer(player, enemy);
        return true;
    } else {
        std::cout << Color::colorize("╔═══════════════════════════════════╗", Color::BRIGHT_RED) << "\n";
        std::cout << Color::colorize("║         💀 DEFEAT... 💀          ║", Color::BOLD + Color::BRIGHT_RED) << "\n";
        std::cout << Color::colorize("╚═══════════════════════════════════╝", Color::BRIGHT_RED) << "\n\n";
        return false;
    }
}

CombatAction CombatSystem::getPlayerAction(CharacterPtr player) {
    std::cout << Color::colorize("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", Color::CYAN) << "\n";
    std::cout << "Choose action:\n";
    std::cout << "  [1] " << Color::colorize("Attack", Color::BRIGHT_RED) << "\n";
    std::cout << "  [2] " << Color::colorize("Use Item", Color::BRIGHT_MAGENTA) << "\n";
    std::cout << "  [3] " << Color::colorize("Run", Color::YELLOW) << "\n";
    std::cout << Color::colorize("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", Color::CYAN) << "\n";

    int choice;
    std::cout << "> ";
    std::cin >> choice;

    if (choice == 2 && !player->getInventory().empty()) {
        player->displayInventory();
        std::cout << "Select item (or -1 to cancel): ";
        int itemIndex;
        std::cin >> itemIndex;

        if (itemIndex >= 0 && itemIndex < static_cast<int>(player->getInventory().size())) {
            player->useItem(itemIndex);
            return CombatAction::USE_ITEM;
        }
    }

    if (choice == 3) {
        return CombatAction::RUN;
    }

    return CombatAction::ATTACK;
}

void CombatSystem::executePlayerTurn(CharacterPtr player, EnemyPtr enemy, CombatAction action) {
    if (action == CombatAction::ATTACK) {
        std::cout << Color::colorize(player->getName(), Color::BRIGHT_CYAN) << " attacks!\n";
        int damage = player->dealDamage();
        enemy->takeDamage(damage);

        if (!enemy->isAlive()) {
            std::cout << Color::colorize(enemy->getName() + " has been defeated!", Color::BRIGHT_GREEN) << "\n";
        }
    }
}

void CombatSystem::executeEnemyTurn(CharacterPtr player, EnemyPtr enemy) {
    std::cout << Color::colorize(enemy->getName(), Color::BRIGHT_RED) << " attacks!\n";
    int damage = enemy->dealDamage();
    player->takeDamage(damage);

    if (!player->isAlive()) {
        std::cout << Color::colorize(player->getName() + " has fallen...", Color::RED) << "\n";
    }
}

void CombatSystem::displayBattleStatus(CharacterPtr player, EnemyPtr enemy) {
    std::cout << Color::colorize("┌─────────────────────────────────┐", Color::CYAN) << "\n";
    std::cout << "│ " << Color::colorize("PLAYER", Color::BOLD + Color::BRIGHT_CYAN) << "\n";
    std::cout << "│ HP: " << Color::colorize(std::to_string(player->getHp()) + "/" + std::to_string(player->getMaxHp()),
                                             Color::BRIGHT_GREEN) << "\n";
    std::cout << Color::colorize("├─────────────────────────────────┤", Color::CYAN) << "\n";
    std::cout << "│ " << Color::colorize("ENEMY", Color::BOLD + Color::BRIGHT_RED) << "\n";
    std::cout << "│ " << enemy->getName() << "\n";
    std::cout << "│ HP: " << Color::colorize(std::to_string(enemy->getHp()) + "/" + std::to_string(enemy->getMaxHp()),
                                             Color::BRIGHT_GREEN) << "\n";
    std::cout << Color::colorize("└─────────────────────────────────┘", Color::CYAN) << "\n\n";
}

void CombatSystem::rewardPlayer(CharacterPtr player, EnemyPtr enemy) {
    int xp = enemy->getXpReward();
    int gold = enemy->getGoldReward();

    player->gainExperience(xp);
    player->addGold(gold);

    std::cout << Color::colorize("Obtained " + std::to_string(gold) + " gold!", Color::BRIGHT_YELLOW) << "\n\n";
}

} // namespace RPG
