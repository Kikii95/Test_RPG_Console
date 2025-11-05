#pragma once

#include <string>
#include <vector>

namespace RPG {

class ConsoleRenderer {
public:
    static void clearScreen();
    static void printTitle(const std::string& title);
    static void printBox(const std::string& content, const std::string& color = "");
    static void printSeparator(char c = '=', int length = 50);
    static void printCentered(const std::string& text);
    static void waitForEnter();
    static void typewriterEffect(const std::string& text, int delayMs = 30);

    static void displayMainMenu();
    static void displayGameOver();
};

} // namespace RPG
