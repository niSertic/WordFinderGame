#pragma once

#include <string>
#include <unordered_set>
#include <chrono>
#include <functional>

namespace WordFinderGame
{
    class GameState
    {
    private:
        std::string m_availableLetters;
        std::unordered_set<std::string> m_foundWords;
        int m_score = 0;
        size_t m_attemptsUsed = 0;
        size_t m_maxAttempts;
        std::chrono::seconds m_timeLimit;
        std::chrono::steady_clock::time_point m_startTime;
        std::function<std::chrono::steady_clock::time_point()> m_now;


    public:
        GameState(
            std::string availableLetters, 
            size_t maxAttempts, 
            std::chrono::seconds timeLimit,
            std::function<std::chrono::steady_clock::time_point()> nowFunc =
            [] { return std::chrono::steady_clock::now(); });

        const std::string& GetAvailableLetters() const;
        const std::unordered_set<std::string>& GetFoundWords() const;
        int GetScore() const;
        size_t GetAttemptsUsed() const;
        size_t GetAttemptsRemaining() const;
        std::chrono::seconds GetTimeRemaining() const;

        bool IsTimeUp() const;
        bool IsAttemptsExceeded() const;
        bool IsGameOver() const;

        void AddWord(const std::string& word, int score);
        void IncrementAttempts();
    };
}