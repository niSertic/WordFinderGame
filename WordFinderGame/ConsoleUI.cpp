#include "ConsoleUI.h"

#include "GameState.h"
#include "GameConfig.h"
#include "HighScoreManager.h"
#include "WordValidator.h"

#include <iostream>
#include <cctype>

namespace WordFinderGame
{
    void ConsoleUI::Clear() const
    {
        std::cout << "\033[2J\033[H";
        std::cout.flush();
    }

    void ConsoleUI::Pause() const
    {
        std::cout << "\nPress Enter to continue...";
        std::string s;
        std::getline(std::cin, s);
    }

    void ConsoleUI::ShowWelcome() const
    {
        std::cout << "=======================================================\n";
        std::cout << "                  WORD FINDER GAME\n";
        std::cout << "=======================================================\n";
        std::cout << "Form words from the given letters.\n"
            << "Type your guess and press Enter.\n"
            << "\nCOMMANDS:\n"
            << "\t- Type /quit and press Enter to exit the game\n"
            << "\t- Press Enter on empty line to refresh 'Time left'\n"
            << "\SCORING:\n"
            << "\t- 3-7 letters: 10-50 pts | 8+ letters: 60 pts\n"
            << "\t- +50 bonus if all letters are used\n"
            << "\nYou have " << GameConfig::TimeLimitSeconds
            << " seconds and " << GameConfig::MaxAttempts
            << " attempts.\n";
        std::cout << "=======================================================\n";
    }

    void ConsoleUI::ShowStatus(const GameState& state) const
    {
        std::cout << "\nLETTERS: "
            << FormatLetters(state.GetAvailableLetters()) << "\n"
            << "Score: " << state.GetScore()
            << " | Attempts left: " << state.GetAttemptsRemaining()
            << " | Time left: " << state.GetTimeRemaining().count()
            << "s\n";
    }

    void ConsoleUI::ShowGameSummary(const GameState& state) const
    {
        std::cout << "\n===== GAME OVER =====\n";
        std::cout << "Final score: " << state.GetScore() << "\n";

        if (!state.GetFoundWords().empty())
        {
            std::cout << "Words found:\n";
            for (const auto& word : state.GetFoundWords())
            {
                std::cout << " - " << word << "\n";
            }
        }
    }

    void ConsoleUI::ShowWordResult(WordValidationResult result, int score) const
    {
        switch (result)
        {
        case WordValidationResult::Valid:
            std::cout << "Accepted! +" << score << " points.\n";
            break;

        case WordValidationResult::TooShort:
            std::cout << "Word is too short.\n";
            break;

        case WordValidationResult::InvalidCharacters:
            std::cout << "Word must contain only letters.\n";
            break;

        case WordValidationResult::NotInDictionary:
            std::cout << "Word not found in dictionary.\n";
            break;

        case WordValidationResult::AlreadyUsed:
            std::cout << "You already found that word.\n";
            break;

        case WordValidationResult::CannotBeFormedFromLetters:
            std::cout << "Word cannot be formed from the given letters.\n";
            break;
        }
    }
   
    void ConsoleUI::ShowTimeUp() const
    {
        std::cout << "\nTime is up!\n";
    }

    void ConsoleUI::ShowHighScores(const std::vector<HighScoreEntry>& scores) const
    {
        if (scores.empty())
            return;

        std::cout << "\n=== High Scores ===\n";
        for (const auto& entry : scores)
        {
            std::cout << entry.playerName
                << " - " << entry.score
                << " (" << entry.timestamp << ")\n";
        }
    }

    std::string ConsoleUI::GetInput() const
    {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    std::string ConsoleUI::PromptForName() const
    {
        std::cout << "\nNew high score! Enter your name: ";
        std::string name;
        std::getline(std::cin, name);
        return name.empty() ? "Player" : name;
    }

    std::string ConsoleUI::FormatLetters(const std::string& letters) const
    {
        std::string formatted;

        for (auto it = letters.begin(); it != letters.end(); ++it)
        {
            if (it != letters.begin())
                formatted.push_back(' ');

            formatted.push_back(static_cast<char>(
                std::toupper(static_cast<unsigned char>(*it))));
        }

        return formatted;
    }
}