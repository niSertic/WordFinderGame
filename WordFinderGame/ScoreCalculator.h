#pragma once

#include <string>

namespace WordFinderGame
{
    class ScoreCalculator
    {
    private:
        static int BaseScoreForLength(size_t length);

    public:
        static int CalculateScore(const std::string& word, const std::string& availableLetters);
    };
}
