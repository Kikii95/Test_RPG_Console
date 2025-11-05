#include "ui/ConsoleRenderer.h"
#include "utils/Color.h"
#include "core/Config.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace RPG {

void ConsoleRenderer::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void ConsoleRenderer::printTitle(const std::string& title) {
    std::cout << Color::colorize("╔════════════════════════════════════════════════╗", Color::BRIGHT_CYAN) << "\n";
    std::cout << Color::colorize("║                                                ║", Color::BRIGHT_CYAN) << "\n";
    std::cout << "║  " << Color::colorize(title, Color::BOLD + Color::BRIGHT_YELLOW) << "\n";
    std::cout << Color::colorize("║                                                ║", Color::BRIGHT_CYAN) << "\n";
    std::cout << Color::colorize("╚════════════════════════════════════════════════╝", Color::BRIGHT_CYAN) << "\n\n";
}

void ConsoleRenderer::printBox(const std::string& content, const std::string& color) {
    std::string boxColor = color.empty() ? Color::WHITE : color;

    std::cout << Color::colorize("┌────────────────────────────────────────────────┐", boxColor) << "\n";
    std::cout << Color::colorize("│ " + content, boxColor) << "\n";
    std::cout << Color::colorize("└────────────────────────────────────────────────┘", boxColor) << "\n";
}

void ConsoleRenderer::printSeparator(char c, int length) {
    std::string separator(length, c);
    std::cout << Color::colorize(separator, Color::BRIGHT_BLUE) << "\n";
}

void ConsoleRenderer::printCentered(const std::string& text) {
    int padding = (50 - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << "\n";
}

void ConsoleRenderer::waitForEnter() {
    std::cout << "\n" << Color::colorize("Press ENTER to continue...", Color::YELLOW);
    std::cin.ignore();
    std::cin.get();
}

void ConsoleRenderer::typewriterEffect(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << "\n";
}

void ConsoleRenderer::displayMainMenu() {
    clearScreen();

    std::cout << Color::colorize(R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║   ██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ███████╗ ██████╗ ███╗  ║
    ║   ██╔══██╗██║   ██║████╗  ██║██╔════╝ ██╔════╝██╔═══██╗████║ ║
    ║   ██║  ██║██║   ██║██╔██╗ ██║██║  ███╗█████╗  ██║   ██║██╔██╗║
    ║   ██║  ██║██║   ██║██║╚██╗██║██║   ██║██╔══╝  ██║   ██║██║╚██║
    ║   ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████╗╚██████╔╝██║ ╚█║
    ║   ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚║
    ║                                                               ║
    ║            ⚔️  CRAWLER RPG - Console Edition  ⚔️            ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝
)", Color::BRIGHT_CYAN + Color::BOLD) << "\n";

    std::cout << Color::colorize("                          " + GAME_VERSION, Color::YELLOW) << "\n\n";

    std::cout << Color::colorize("    [1] New Game", Color::BRIGHT_GREEN) << "\n";
    std::cout << Color::colorize("    [2] Instructions", Color::BRIGHT_BLUE) << "\n";
    std::cout << Color::colorize("    [3] Exit", Color::BRIGHT_RED) << "\n\n";

    printSeparator('═', 65);
}

void ConsoleRenderer::displayGameOver() {
    clearScreen();

    std::cout << Color::colorize(R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║      ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ║
    ║     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ║
    ║     ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ║
    ║     ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗  ║
    ║     ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ██║  ║
    ║      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝  ╚═╝  ║
    ║                  ╚═╝ ╚═╝╚═╝                                  ║
    ╚═══════════════════════════════════════════════════════════════╝
)", Color::BRIGHT_RED + Color::BOLD) << "\n\n";
}

} // namespace RPG
