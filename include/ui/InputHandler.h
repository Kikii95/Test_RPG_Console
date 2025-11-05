#pragma once

#include <string>

namespace RPG {

class InputHandler {
public:
    static int getMenuChoice(int min, int max);
    static std::string getPlayerName();
    static bool confirmAction(const std::string& prompt);
};

} // namespace RPG
