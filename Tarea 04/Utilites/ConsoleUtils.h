#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <string>
#include <vector>

namespace ConsoleUtils
{

    class ConsoleMenu
    {
    private:
        static std::vector<std::string> options;
        static int counter;

    public:
        static void addMenuOption(const std::string &option);
        static void showMenuOption();
        static bool shouldContinue(const std::string &userInput);
        static bool askYesNo(const std::string &question);
        static void printSeparator(const std::string &title = "");
        static void clearMenuOptions();
        static std::string shouldReturnToMenu();
    };

}

#endif
