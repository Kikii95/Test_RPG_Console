#include "ui/InputHandler.h"
#include "utils/Color.h"
#include <iostream>
#include <limits>

namespace RPG {

int InputHandler::getMenuChoice(int min, int max) {
    int choice;

    while (true) {
        std::cout << Color::colorize("Select option: ", Color::BRIGHT_CYAN);
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << Color::colorize("Invalid input! Please enter a number.", Color::RED) << "\n";
            continue;
        }

        if (choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        std::cout << Color::colorize("Invalid choice! Select between " + std::to_string(min) +
                                     " and " + std::to_string(max) + ".", Color::RED) << "\n";
    }
}

std::string InputHandler::getPlayerName() {
    std::string name;

    std::cout << Color::colorize("Enter your hero's name: ", Color::BRIGHT_CYAN);
    std::getline(std::cin, name);

    if (name.empty()) {
        name = "Hero";
    }

    return name;
}

bool InputHandler::confirmAction(const std::string& prompt) {
    std::cout << Color::colorize(prompt + " (y/n): ", Color::YELLOW);

    char response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return (response == 'y' || response == 'Y');
}

} // namespace RPG
