#include "ConsoleUtils.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

namespace ConsoleUtils
{

    std::vector<std::string> ConsoleMenu::options;
    int ConsoleMenu::counter = 0;

    void ConsoleMenu::addMenuOption(const std::string &option)
    {
        counter++;
        options.push_back(std::to_string(counter) + ".) " + option);
    }

    void ConsoleMenu::clearMenuOptions()
    {
        options.clear();
    }

    void ConsoleMenu::showMenuOption()
    {
        std::cout << "\n=== MENÚ PRINCIPAL ===\n\n";
        for (const auto &opt : options)
        {
            std::cout << opt << std::endl;
        }
        std::cout << "\nSeleccione una opción (1-" << options.size() << "): ";
    }

    bool ConsoleMenu::shouldContinue(const string &userInput)
    {
        string inputLower = userInput;
        transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
        return inputLower == "yes" || inputLower == "y";
    }

    bool ConsoleMenu::askYesNo(const string &question)
    {
        string input;
        cout << question << " (yes/no): ";
        cin >> input;
        return shouldContinue(input);
    }

    void ConsoleMenu::printSeparator(const string &title)
    {
        cout << "\n"
             << title << endl;
        cout << "----------------------------------------" << endl;
        cout << "----------------------------------------" << endl;
    }
    std::string ConsoleMenu::shouldReturnToMenu()
    {
        std::string continueInput;
        cout << "\n¿Deseas regresar al menú? (yes/no): ";
        cin >> continueInput;
        return continueInput;
    }
}