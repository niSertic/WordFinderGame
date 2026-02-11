
#pragma once

#include <string>
#include <vector>

namespace WordFinderGame
{
    class GameState;
    struct HighScoreEntry;
    enum class WordValidationResult;

    class ConsoleUI
    {
    public:
        void Clear() const;
        void Pause() const;

        void ShowWelcome() const;
        void ShowStatus(const GameState& state) const;
        void ShowGameSummary(const GameState& state) const;
        void ShowWordResult(WordValidationResult result, int score) const;
        void ShowTimeUp() const;
        void ShowHighScores(const std::vector<HighScoreEntry>& scores) const;

        std::string GetInput() const;
        std::string PromptForName() const;

    private:
        std::string FormatLetters(const std::string& letters) const;
    };
}
