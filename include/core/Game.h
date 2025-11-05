#pragma once

#include "entities/Character.h"
#include "entities/Enemy.h"
#include "entities/Weapon.h"
#include "entities/Potion.h"
#include <memory>

namespace RPG {

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    QUIT
};

class Game {
public:
    Game();
    void run();

private:
    GameState state;
    CharacterPtr player;

    void initializeGame();
    void showMainMenu();
    void showInstructions();
    void gameLoop();
    void exploreArea();
    void showPlayerMenu();
    void handleShop();
    void giveStarterItems();

    bool isRunning() const { return state != GameState::QUIT; }
};

} // namespace RPG
