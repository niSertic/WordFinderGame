#pragma once

#include <string>

#include "Dictionary.h"
#include "WordValidator.h"
#include "HighScoreManager.h"
#include "ConsoleUI.h"

namespace WordFinderGame
{
    class GameState;

    class GameController
    {
    private:
        std::string m_dictionaryPath;
        std::string m_highScoreFilePath;

        ConsoleUI m_ui;
        Dictionary m_dictionary;
        WordValidator m_validator;
        HighScoreManager m_highScores;

        bool ProcessSingleTurn(GameState& state);

        void HandleHighScores(const GameState& state);

    public:
        GameController(std::string dictionaryPath, std::string highScoreFilePath);
        void Run();
    };
}