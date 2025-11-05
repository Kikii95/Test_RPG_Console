#pragma once

#include <string>

namespace RPG {

constexpr int STARTING_LEVEL = 1;
constexpr int STARTING_HP = 100;
constexpr int STARTING_MANA = 50;
constexpr int STARTING_ATTACK = 10;
constexpr int STARTING_DEFENSE = 5;

constexpr int MAX_INVENTORY_SIZE = 20;
constexpr int LEVEL_UP_HP_GAIN = 20;
constexpr int LEVEL_UP_MANA_GAIN = 10;
constexpr int LEVEL_UP_ATTACK_GAIN = 3;
constexpr int LEVEL_UP_DEFENSE_GAIN = 2;

constexpr int BASE_XP_REQUIREMENT = 100;
constexpr float XP_SCALING_FACTOR = 1.5f;

const std::string GAME_TITLE = "DUNGEON CRAWLER RPG";
const std::string GAME_VERSION = "v0.1.0";

} // namespace RPG
