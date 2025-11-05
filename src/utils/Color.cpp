#include "utils/Color.h"

namespace RPG {

const std::string Color::RESET = "\033[0m";
const std::string Color::BOLD = "\033[1m";

const std::string Color::BLACK = "\033[30m";
const std::string Color::RED = "\033[31m";
const std::string Color::GREEN = "\033[32m";
const std::string Color::YELLOW = "\033[33m";
const std::string Color::BLUE = "\033[34m";
const std::string Color::MAGENTA = "\033[35m";
const std::string Color::CYAN = "\033[36m";
const std::string Color::WHITE = "\033[37m";

const std::string Color::BRIGHT_RED = "\033[91m";
const std::string Color::BRIGHT_GREEN = "\033[92m";
const std::string Color::BRIGHT_YELLOW = "\033[93m";
const std::string Color::BRIGHT_BLUE = "\033[94m";
const std::string Color::BRIGHT_MAGENTA = "\033[95m";
const std::string Color::BRIGHT_CYAN = "\033[96m";
const std::string Color::BRIGHT_WHITE = "\033[97m";

const std::string Color::BG_BLACK = "\033[40m";
const std::string Color::BG_RED = "\033[41m";
const std::string Color::BG_DARK_GRAY = "\033[100m";

std::string Color::colorize(const std::string& text, const std::string& color) {
    return color + text + RESET;
}

} // namespace RPG
