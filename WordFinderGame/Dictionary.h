#pragma once

#include <string>
#include <unordered_set>

namespace WordFinderGame
{
    class Dictionary
    {

    private:
        std::unordered_set<std::string> m_words;

        static std::string NormalizeWord(const std::string& word);
        static bool IsValidWord(const std::string& word);

    public:
        Dictionary() = default;

        bool LoadFromFile(const std::string& filePath);

        bool Contains(const std::string& word) const;

        size_t Size() const;

        void Clear();

    };
}
