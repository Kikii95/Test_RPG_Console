#pragma once

#include <string>

namespace RPG {

class Color {
public:
    static const std::string RESET;
    static const std::string BOLD;

    // Basic colors
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;

    // Bright colors
    static const std::string BRIGHT_RED;
    static const std::string BRIGHT_GREEN;
    static const std::string BRIGHT_YELLOW;
    static const std::string BRIGHT_BLUE;
    static const std::string BRIGHT_MAGENTA;
    static const std::string BRIGHT_CYAN;
    static const std::string BRIGHT_WHITE;

    // Background colors
    static const std::string BG_BLACK;
    static const std::string BG_RED;
    static const std::string BG_DARK_GRAY;

    static std::string colorize(const std::string& text, const std::string& color);
};

} // namespace RPG
