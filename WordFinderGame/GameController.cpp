#include "GameController.h"

#include "LetterSetGenerator.h"
#include "ScoreCalculator.h"
#include "GameState.h"
#include "GameConfig.h"

#include <chrono>
#include <iostream>


namespace WordFinderGame
{
    GameController::GameController(std::string dictionaryPath, std::string highScoreFilePath)
        : m_dictionaryPath(std::move(dictionaryPath))
        , m_highScoreFilePath(std::move(highScoreFilePath))
        , m_highScores(m_highScoreFilePath,
            GameConfig::MaxHighScoreEntries)
    {
    }

    void GameController::Run()
    {
        if (!m_dictionary.LoadFromFile(m_dictionaryPath))
        {
            std::cout << "Failed to load dictionary file.\n";
            return;
        }

        m_ui.Clear();
        m_ui.ShowWelcome();
        m_ui.Pause();

        LetterSetGenerator generator;
        const std::string letters = generator.Generate(GameConfig::LetterCount);

        GameState state(
            letters,
            GameConfig::MaxAttempts,
            std::chrono::seconds(GameConfig::TimeLimitSeconds));

        while (!state.IsGameOver())
        {
            if (!ProcessSingleTurn(state))
            {
                break;
            }
        }

        m_ui.Clear();
        m_ui.ShowWelcome();
        m_ui.ShowGameSummary(state);
        HandleHighScores(state);
    }

   
    bool GameController::ProcessSingleTurn(GameState& state)
        
    {
        m_ui.Clear();
        m_ui.ShowWelcome();
        m_ui.ShowStatus(state);

        if (state.IsTimeUp())
        {
            m_ui.ShowTimeUp();
            m_ui.Pause();
            return false;
        }

        const std::string input = m_ui.GetInput();

        if (state.IsTimeUp())
        {
            m_ui.ShowTimeUp();
            m_ui.Pause();
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

        const auto result = m_validator.Validate(
            input,
            state.GetAvailableLetters(),
            state.GetFoundWords(),
            m_dictionary);

        int score = 0;

        if (result == WordValidationResult::Valid)
        {
            score = ScoreCalculator::CalculateScore(input, state.GetAvailableLetters());
            state.AddWord(input, score);
        }

        m_ui.ShowWordResult(result, score);
        m_ui.Pause();

        return true;
    }

    void GameController::HandleHighScores(const GameState& state)
    {

		// Loads existing high scores and checks if the player's score qualifies for the leaderboard.

        auto scores = m_highScores.Load();

        if (state.GetScore() > 0 &&
            m_highScores.QualifiesForHighScore(scores, state.GetScore()))
        {
            HighScoreEntry entry{
                m_ui.PromptForName(),
                state.GetScore(),
                HighScoreManager::CreateTimestamp()
            };

            scores = m_highScores.AddNewScore(scores, entry);
        }

        m_ui.ShowHighScores(scores);
    }
}