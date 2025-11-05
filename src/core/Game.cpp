#include "core/Game.h"
#include "core/Config.h"
#include "systems/CombatSystem.h"
#include "systems/EnemyFactory.h"
#include "ui/ConsoleRenderer.h"
#include "ui/InputHandler.h"
#include "utils/Color.h"
#include "utils/Random.h"
#include <iostream>

namespace RPG {

Game::Game() : state(GameState::MENU), player(nullptr) {}

void Game::run() {
    while (isRunning()) {
        switch (state) {
            case GameState::MENU:
                showMainMenu();
                break;

            case GameState::PLAYING:
                gameLoop();
                break;

            case GameState::GAME_OVER:
                ConsoleRenderer::displayGameOver();
                ConsoleRenderer::waitForEnter();
                state = GameState::MENU;
                break;

            case GameState::QUIT:
                break;
        }
    }

    std::cout << Color::colorize("\nThanks for playing!\n", Color::BRIGHT_CYAN);
}

void Game::initializeGame() {
    ConsoleRenderer::clearScreen();

    std::cout << Color::colorize("╔═══════════════════════════════════╗", Color::BRIGHT_YELLOW) << "\n";
    std::cout << Color::colorize("║      CHARACTER CREATION          ║", Color::BRIGHT_YELLOW) << "\n";
    std::cout << Color::colorize("╚═══════════════════════════════════╝", Color::BRIGHT_YELLOW) << "\n\n";

    std::string name = InputHandler::getPlayerName();

    player = std::make_shared<Character>(name, STARTING_HP, STARTING_MANA,
                                        STARTING_ATTACK, STARTING_DEFENSE);

    ConsoleRenderer::clearScreen();
    std::cout << "\n" << Color::colorize("Welcome, " + name + "!", Color::BRIGHT_CYAN) << "\n";
    ConsoleRenderer::typewriterEffect("Your adventure in the dark dungeons begins now...");

    giveStarterItems();

    ConsoleRenderer::waitForEnter();
    state = GameState::PLAYING;
}

void Game::giveStarterItems() {
    auto starterWeapon = std::make_shared<Weapon>("Iron Sword", "A basic but reliable blade",
                                                  5, WeaponType::SWORD);
    auto starterPotion = std::make_shared<Potion>("Health Potion", "Restores 50 HP",
                                                  50, PotionType::HEALTH);

    player->addItem(starterWeapon);
    player->addItem(starterPotion);
    player->addItem(starterPotion);

    player->equipWeapon(0);
}

void Game::showMainMenu() {
    ConsoleRenderer::displayMainMenu();

    int choice = InputHandler::getMenuChoice(1, 3);

    switch (choice) {
        case 1:
            initializeGame();
            break;

        case 2:
            showInstructions();
            break;

        case 3:
            state = GameState::QUIT;
            break;
    }
}

void Game::showInstructions() {
    ConsoleRenderer::clearScreen();
    ConsoleRenderer::printTitle("INSTRUCTIONS");

    std::cout << Color::colorize("OBJECTIVE:", Color::BOLD + Color::BRIGHT_YELLOW) << "\n";
    std::cout << "  Explore dungeons, fight enemies, and level up your character.\n\n";

    std::cout << Color::colorize("COMBAT:", Color::BOLD + Color::BRIGHT_RED) << "\n";
    std::cout << "  - Choose to Attack, Use Items, or Run from battles\n";
    std::cout << "  - Defeat enemies to gain XP and gold\n";
    std::cout << "  - Level up to increase your stats\n\n";

    std::cout << Color::colorize("ITEMS:", Color::BOLD + Color::BRIGHT_MAGENTA) << "\n";
    std::cout << "  - Equip weapons to increase attack power\n";
    std::cout << "  - Use potions to restore HP and MP\n";
    std::cout << "  - Visit shops to buy new items\n\n";

    std::cout << Color::colorize("TIPS:", Color::BOLD + Color::BRIGHT_CYAN) << "\n";
    std::cout << "  - Always keep healing potions in your inventory\n";
    std::cout << "  - Don't fight enemies much stronger than you\n";
    std::cout << "  - Explore carefully and manage your resources\n\n";

    ConsoleRenderer::waitForEnter();
}

void Game::gameLoop() {
    while (state == GameState::PLAYING && player->isAlive()) {
        showPlayerMenu();
    }

    if (!player->isAlive()) {
        state = GameState::GAME_OVER;
    }
}

void Game::showPlayerMenu() {
    ConsoleRenderer::clearScreen();
    ConsoleRenderer::printTitle("DUNGEON EXPLORATION");

    player->displayStats();

    std::cout << "\n" << Color::colorize("═════════════════════════════════════", Color::BRIGHT_BLUE) << "\n";
    std::cout << Color::colorize("What would you like to do?", Color::BOLD) << "\n\n";
    std::cout << "  [1] " << Color::colorize("Explore deeper into dungeon", Color::BRIGHT_GREEN) << "\n";
    std::cout << "  [2] " << Color::colorize("Check inventory", Color::BRIGHT_MAGENTA) << "\n";
    std::cout << "  [3] " << Color::colorize("Visit shop", Color::BRIGHT_YELLOW) << "\n";
    std::cout << "  [4] " << Color::colorize("Rest (restore HP/MP)", Color::CYAN) << "\n";
    std::cout << "  [5] " << Color::colorize("Return to main menu", Color::RED) << "\n";
    std::cout << Color::colorize("═════════════════════════════════════", Color::BRIGHT_BLUE) << "\n\n";

    int choice = InputHandler::getMenuChoice(1, 5);

    switch (choice) {
        case 1:
            exploreArea();
            break;

        case 2:
            ConsoleRenderer::clearScreen();
            player->displayInventory();
            ConsoleRenderer::waitForEnter();
            break;

        case 3:
            handleShop();
            break;

        case 4:
            player->setHp(player->getMaxHp());
            player->setMana(player->getMaxMana());
            std::cout << Color::colorize("\nYou rest and recover fully.", Color::BRIGHT_GREEN) << "\n";
            ConsoleRenderer::waitForEnter();
            break;

        case 5:
            if (InputHandler::confirmAction("Are you sure you want to quit?")) {
                state = GameState::MENU;
            }
            break;
    }
}

void Game::exploreArea() {
    ConsoleRenderer::clearScreen();

    std::cout << "\n" << Color::colorize("You venture deeper into the darkness...", Color::YELLOW) << "\n\n";

    ConsoleRenderer::waitForEnter();

    if (Random::getInstance().chance(0.8f)) {
        EnemyPtr enemy = EnemyFactory::createRandomEnemy(player->getLevel());
        bool victory = CombatSystem::startBattle(player, enemy);

        if (victory && Random::getInstance().chance(0.3f)) {
            auto loot = std::make_shared<Potion>("Health Potion", "Restores 50 HP",
                                                50, PotionType::HEALTH);
            player->addItem(loot);
        }

        ConsoleRenderer::waitForEnter();
    } else {
        std::cout << Color::colorize("You found a safe area. Nothing here...", Color::CYAN) << "\n";
        ConsoleRenderer::waitForEnter();
    }
}

void Game::handleShop() {
    ConsoleRenderer::clearScreen();
    ConsoleRenderer::printTitle("SHOP");

    std::cout << "Your gold: " << Color::colorize(std::to_string(player->getGold()), Color::BRIGHT_YELLOW) << "\n\n";

    std::cout << "  [1] " << Color::colorize("Health Potion", Color::BRIGHT_MAGENTA) << " - 30 gold\n";
    std::cout << "  [2] " << Color::colorize("Mana Potion", Color::BRIGHT_BLUE) << " - 25 gold\n";
    std::cout << "  [3] " << Color::colorize("Steel Sword", Color::BRIGHT_YELLOW) << " - 100 gold (+10 ATK)\n";
    std::cout << "  [4] " << Color::colorize("Exit shop", Color::RED) << "\n\n";

    int choice = InputHandler::getMenuChoice(1, 4);

    if (choice == 1 && player->getGold() >= 30) {
        player->addGold(-30);
        auto potion = std::make_shared<Potion>("Health Potion", "Restores 50 HP", 50, PotionType::HEALTH);
        player->addItem(potion);
        std::cout << Color::colorize("Purchased Health Potion!", Color::BRIGHT_GREEN) << "\n";
    } else if (choice == 2 && player->getGold() >= 25) {
        player->addGold(-25);
        auto potion = std::make_shared<Potion>("Mana Potion", "Restores 30 MP", 30, PotionType::MANA);
        player->addItem(potion);
        std::cout << Color::colorize("Purchased Mana Potion!", Color::BRIGHT_GREEN) << "\n";
    } else if (choice == 3 && player->getGold() >= 100) {
        player->addGold(-100);
        auto weapon = std::make_shared<Weapon>("Steel Sword", "A sharp blade forged in fire", 10, WeaponType::SWORD);
        player->addItem(weapon);
        std::cout << Color::colorize("Purchased Steel Sword!", Color::BRIGHT_GREEN) << "\n";
    } else if (choice == 4) {
        return;
    } else {
        std::cout << Color::colorize("Not enough gold!", Color::RED) << "\n";
    }

    ConsoleRenderer::waitForEnter();
}

} // namespace RPG
