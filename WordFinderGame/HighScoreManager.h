#pragma once

#include <string>
#include <vector>

namespace WordFinderGame
{
    struct HighScoreEntry
    {
        std::string playerName;
        int score;
        std::string timestamp;
    };

    class HighScoreManager
    {
    private:
        std::string m_filePath;
        size_t m_maxEntries;

        static bool CompareByScore(const HighScoreEntry& a, const HighScoreEntry& b);

    public:
        explicit HighScoreManager(std::string filePath, size_t maxEntries = 10);

        std::vector<HighScoreEntry> Load() const;

        void Save(const std::vector<HighScoreEntry>& scores) const;

        std::vector<HighScoreEntry> AddNewScore(std::vector<HighScoreEntry>& scores, const HighScoreEntry& entry) const;

        bool QualifiesForHighScore(const std::vector<HighScoreEntry>& scores, int score) const;

        static std::string CreateTimestamp();
    };
}
