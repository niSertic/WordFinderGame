#pragma once

#include <string>

namespace WordFinderGame
{
    class Dictionary;
    class GameState;
    class WordValidator;
    class HighScoreManager;

    enum class WordValidationResult;

    class GameController
    {
    private:
        std::string m_dictionaryPath;
        std::string m_highScoreFilePath;

        bool ProcessSingleTurn(
            GameState& state,
            const Dictionary& dictionary,
            WordValidator& validator);

        void HandleHighScores(const GameState& state, HighScoreManager& highScores);

        void PrintWelcome() const;
        void PrintStatus(const GameState& state) const;
        void PrintGameSummary(const GameState& state) const;
        void PrintValidationMessage(WordValidationResult result) const;

        std::string FormatLetters(const std::string& letters) const;

    public:
        GameController(std::string dictionaryPath, std::string highScoreFilePath);
        void Run();
    };
}