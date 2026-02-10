#pragma once

namespace WordFinderGame
{
    struct GameConfig
    {
        static constexpr int MaxAttempts = 25;
        static constexpr int TimeLimitSeconds = 60;
        static constexpr int LetterCount = 9;

        static constexpr int MaxHighScoreEntries = 5;
    };
}