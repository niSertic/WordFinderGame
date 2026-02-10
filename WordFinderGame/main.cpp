#include "GameController.h"

#include <iostream>

int main()
{
    const std::string dictionaryPath = "dictionary.txt";
    const std::string highScorePath = "highscores.txt";

    while (true)
    {
        WordFinderGame::GameController controller(dictionaryPath, highScorePath);
        controller.Run();

        std::cout << "\nPlay another round? (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);

        if (answer.empty() || (answer[0] != 'y' && answer[0] != 'Y'))
        {
            break;
        }
    }

    std::cout << "\nThanks for playing!\n";
    return 0;
}