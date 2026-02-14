#include "WordValidator.h"
#include "Dictionary.h"

#include <algorithm>
#include <cctype>
#include <unordered_map>


namespace WordFinderGame
{

    WordValidationResult WordValidator::Validate(
        const std::string& word,
        const std::string& availableLetters,
        const std::unordered_set<std::string>& usedWords,
        const Dictionary& dictionary) const
    {
        std::string normalized = word;
        std::transform(normalized.begin(), normalized.end(),normalized.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(std::tolower(c));
            });

        if (normalized.length() < 3)
        {
            return WordValidationResult::TooShort;
        }

        if (!HasOnlyLetters(normalized))
        {
            return WordValidationResult::InvalidCharacters;
        }

        if (!CanBeFormedFromLetters(normalized, availableLetters))
        {
            return WordValidationResult::CannotBeFormedFromLetters;
        }

        if (usedWords.contains(normalized))
        {
            return WordValidationResult::AlreadyUsed;
        }

        if (!dictionary.Contains(normalized))
        {
            return WordValidationResult::NotInDictionary;
        }

        return WordValidationResult::Valid;
    }

    bool WordValidator::HasOnlyLetters(const std::string& word)
    {
        return std::all_of(word.begin(), word.end(),
            [](unsigned char c)
            {
                return std::isalpha(c);
            });
    }

    bool WordValidator::CanBeFormedFromLetters(const std::string& word, const std::string& availableLetters)
    {
        std::unordered_map<char, size_t> letterCounts;

        for (char c : availableLetters)
        {
            ++letterCounts[c];
        }

        for (char c : word)
        {
            auto it = letterCounts.find(c);
            if (it == letterCounts.end() || it->second == 0)
            {
                return false;
            }

            --it->second;
        }

        return true;
    }
}