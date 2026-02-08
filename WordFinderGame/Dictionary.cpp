#include "Dictionary.h"

#include <fstream>
#include <algorithm>
#include <cctype>

namespace WordFinderGame
{
    bool Dictionary::LoadFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file)
        {
            return false;
        }

        m_words.clear();

        std::string line;
        while (std::getline(file, line))
        {
            const std::string normalized = NormalizeWord(line);

            if (IsValidWord(normalized))
            {
                m_words.insert(normalized);
            }
        }

        return true;
    }

    bool Dictionary::Contains(const std::string& word) const
    {
        return m_words.contains(word);
    }

    size_t Dictionary::Size() const
    {
        return m_words.size();
    }

    void Dictionary::Clear()
    {
        m_words.clear();
    }

    std::string Dictionary::NormalizeWord(const std::string& word)
    {
        std::string result = word;

        std::transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(std::tolower(c));
            });

        return result;
    }

    bool Dictionary::IsValidWord(const std::string& word)
    {
        return word.length() >= 3 &&
            std::all_of(word.begin(), word.end(),
                [](unsigned char c)
                {
                    return std::isalpha(c);
                });
    }
}//