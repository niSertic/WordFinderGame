#include "GameController.h"

#include "Dictionary.h"
#include "LetterSetGenerator.h"
#include "WordValidator.h"
#include "ScoreCalculator.h"
#include "GameState.h"
#include "HighScoreManager.h"
#include "GameConfig.h"

#include <iostream>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <sstream>

namespace
{
    void ClearScreen()
    {
        std::cout << "\033[2J\033[H";
        std::cout.flush();
    }

    void PauseForUser()
    {
        std::cout << "\nPress Enter to continue...";
        std::string s;
        std::getline(std::cin, s);
    }

    std::string GetCurrentTimestamp()
    {
        auto now = std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now());
        return std::format("{:%Y-%m-%d %H:%M}", now);
    }
}

namespace WordFinderGame
{
    GameController::GameController(std::string dictionaryPath, std::string highScoreFilePath)
        : m_dictionaryPath(std::move(dictionaryPath))
        , m_highScoreFilePath(std::move(highScoreFilePath))
    {
    }

    void GameController::Run()
    {
        Dictionary dictionary;
        HighScoreManager highScores(m_highScoreFilePath, GameConfig::MaxHighScoreEntries);
        WordValidator validator;

        if (!dictionary.LoadFromFile(m_dictionaryPath))
        {
            std::cout << "Failed to load dictionary file.\n";
            return;
        }

        ClearScreen();
        PrintWelcome();
        PauseForUser();

        LetterSetGenerator letterGenerator;
        const std::string letters = letterGenerator.Generate(GameConfig::LetterCount);

        GameState state(
            letters,
            GameConfig::MaxAttempts,
            std::chrono::seconds(GameConfig::TimeLimitSeconds));

        while (!state.IsGameOver())
        {
            if (!ProcessSingleTurn(state, dictionary, validator))
            {
                break;
            }
        }

        ClearScreen();
        PrintWelcome();
        PrintGameSummary(state);
        HandleHighScores(state, highScores);
    }

    

    bool GameController::ProcessSingleTurn(
        GameState& state,
        const Dictionary& dictionary,
        WordValidator& validator)
    {
        ClearScreen();
        PrintWelcome();
        PrintStatus(state);

        if (state.IsTimeUp())
        {
            std::cout << "\nTime is up!\n";
            PauseForUser();
            return false;
        }

        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        if (state.IsTimeUp())
        {
            std::cout << "\nTime is up!\n";
            PauseForUser();
            return false;
        }

        if (input.empty())
        {
            return true;
        }

        if (input == "/quit")
        {
            return false;
        }

        state.IncrementAttempts();

        const auto result = validator.Validate(
            input,
            state.GetAvailableLetters(),
            state.GetFoundWords(),
            dictionary);

        if (result != WordValidationResult::Valid)
        {
            PrintValidationMessage(result);
            PauseForUser();
            return true;
        }

        const int score = ScoreCalculator::CalculateScore(input, state.GetAvailableLetters());

        state.AddWord(input, score);

        std::cout << "Accepted! +" << score << " points.\n";
        PauseForUser();
        return true;
    }

    void GameController::HandleHighScores(const GameState& state, HighScoreManager& highScores)
    {
        auto existingScores = highScores.Load();

        const bool qualifies =
            existingScores.size() < GameConfig::MaxHighScoreEntries ||
            std::any_of(existingScores.begin(), existingScores.end(),
                [&](const HighScoreEntry& e)
                {
                    return state.GetScore() > e.score;
                });

        if (qualifies && state.GetScore() > 0)
        {
            std::cout << "\nNew high score! Enter your name: ";
            std::string name;
            std::getline(std::cin, name);

            if (name.empty())
            {
                name = "Player";
            }

            HighScoreEntry entry{
                name,
                state.GetScore(),
                GetCurrentTimestamp()
            };

            existingScores = highScores.AddNewScore(entry);
        }

        if (!existingScores.empty())
        {
            std::cout << "\n=== High Scores ===\n";
            for (const auto& entry : existingScores)
            {
                std::cout << entry.playerName
                    << " - " << entry.score
                    << " (" << entry.timestamp << ")\n";
            }
        }
    }

    void GameController::PrintWelcome() const
    {
        std::cout << "=======================================================\n";
        std::cout << "                  WORD FINDER GAME\n";
        std::cout << "=======================================================\n";
        std::cout << "Form words from the given letters.\n"
            << "Type your guess and press Enter.\n"
            << "\nCOMMANDS: \n\t- Type /quit and press Enter to exit the game\n"
            << "\t- Press Enter on empty line to refresh 'Time left'\n"
            << "\nYou have " << GameConfig::TimeLimitSeconds << " seconds and "
            << GameConfig::MaxAttempts << " attempts.\n";
        std::cout << "=======================================================\n";
    }

    void GameController::PrintStatus(const GameState& state) const
    {
        std::cout << "\nLETTERS: "
            << FormatLetters(state.GetAvailableLetters()) << "\n"
            << "Score: " << state.GetScore()
            << " | Attempts left: " << state.GetAttemptsRemaining()
            << " | Time left: " << state.GetTimeRemaining().count()
            << "s\n";
    }

    void GameController::PrintGameSummary(const GameState& state) const
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

    void GameController::PrintValidationMessage(
        WordValidationResult result) const
    {
        switch (result)
        {
        case WordValidationResult::TooShort:
            std::cout << "Word is too short (minimum " << 3 << " letters).\n";
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
        default:
            std::cout << "Invalid word.\n";
            break;
        }
    }

    std::string GameController::FormatLetters(const std::string& letters) const
    {
        std::string formatted;

        for (auto it = letters.begin(); it != letters.end(); ++it)
        {
            if (it != letters.begin())
            {
                formatted.push_back(' ');
            }
            formatted.push_back(static_cast<char>(
                std::toupper(static_cast<unsigned char>(*it))));
        }

        return formatted;
    }
}