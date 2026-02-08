#include "ScoreCalculator.h"

namespace WordFinderGame
{
    int ScoreCalculator::CalculateScore(const std::string& word, const std::string& availableLetters)
    {
        const size_t length = word.length();

        int score = BaseScoreForLength(length);

        if (length == availableLetters.length())
        {
            score += 50;
        }

        return score;
    }

    int ScoreCalculator::BaseScoreForLength(size_t length)
    {
        switch (length)
        {
        case 3: return 10;
        case 4: return 20;
        case 5: return 30;
        case 6: return 40;
        case 7: return 50;
        default:
            return (length >= 8) ? 60 : 0;
        }
    }
}