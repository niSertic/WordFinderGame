#include "HighScoreManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace WordFinderGame
{
    HighScoreManager::HighScoreManager(std::string filePath, size_t maxEntries)
        : m_filePath(std::move(filePath)), m_maxEntries(maxEntries)
    {
    }

    std::vector<HighScoreEntry> HighScoreManager::Load() const
    {
        std::vector<HighScoreEntry> scores;

        std::ifstream file(m_filePath);
        if (!file)
        {
            return scores;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string name;
            std::string scoreStr;
            std::string timestamp;

            if (!std::getline(ss, name, ';'))
                continue;
            if (!std::getline(ss, scoreStr, ';'))
                continue;
            if (!std::getline(ss, timestamp))
                continue;
            
            try
            {
                int score = std::stoi(scoreStr);
                scores.push_back({ name, score, timestamp });
            }
            catch (const std::invalid_argument&)
            {
                continue;
            }
            catch (const std::out_of_range&)
            {
                continue;
            }
        }

        return scores;
    }

    void HighScoreManager::Save(const std::vector<HighScoreEntry>& scores) const
    {
        std::ofstream file(m_filePath, std::ios::trunc);
        if (!file)
        {
            return;
        }

        for (const auto& entry : scores)
        {
            file << entry.playerName << ';'
                << entry.score << ';'
                << entry.timestamp << '\n';
        }
    }

    std::vector<HighScoreEntry> HighScoreManager::AddNewScore(
        const HighScoreEntry& entry) const
    {
        auto scores = Load();

        scores.push_back(entry);

        std::sort(scores.begin(), scores.end(), CompareByScore);

        if (scores.size() > m_maxEntries)
        {
            scores.resize(m_maxEntries);
        }

        Save(scores);

        return scores;
    }

    bool HighScoreManager::CompareByScore(
        const HighScoreEntry& a,
        const HighScoreEntry& b)
    {
        return a.score > b.score;
    }
}