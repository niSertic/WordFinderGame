#include "GameState.h"

#include <algorithm>


namespace WordFinderGame
{

    GameState::GameState(std::string availableLetters, size_t maxAttempts, std::chrono::seconds timeLimit)
        : m_availableLetters(std::move(availableLetters))
        , m_maxAttempts(maxAttempts)
        , m_timeLimit(timeLimit)
        , m_startTime(std::chrono::steady_clock::now())
    {
    }

    const std::string& GameState::GetAvailableLetters() const
    {
        return m_availableLetters;
    }

    const std::unordered_set<std::string>& GameState::GetFoundWords() const
    {
        return m_foundWords;
    }

    int GameState::GetScore() const
    {
        return m_score;
    }

    size_t GameState::GetAttemptsUsed() const
    {
        return m_attemptsUsed;
    }

    size_t GameState::GetAttemptsRemaining() const
    {
        return (m_attemptsUsed >= m_maxAttempts) ? 0 : (m_maxAttempts - m_attemptsUsed);
    }

    std::chrono::seconds GameState::GetTimeRemaining() const
    {
        const auto elapsed = duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_startTime);

        if (elapsed >= m_timeLimit)
        {
            return std::chrono::seconds(0);
        }

        return m_timeLimit - elapsed;
    }

    bool GameState::IsTimeUp() const
    {
        return GetTimeRemaining().count() == 0;
    }

    bool GameState::IsAttemptsExceeded() const
    {
        return m_attemptsUsed >= m_maxAttempts;
    }

    bool GameState::IsGameOver() const
    {
        return IsTimeUp() || IsAttemptsExceeded();
    }

    void GameState::AddWord(const std::string& word, int score)
    {
        m_foundWords.insert(word);
        m_score += score;
    }

    void GameState::IncrementAttempts()
    {
        ++m_attemptsUsed;
    }
}