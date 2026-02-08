#pragma once

#include <string>
#include <unordered_set>


namespace WordFinderGame
{
    class Dictionary;

    enum class WordValidationResult
    {
        Valid,
        TooShort,
        InvalidCharacters,
        NotInDictionary,
        AlreadyUsed,
        CannotBeFormedFromLetters
    };

    class WordValidator
    {
    private:
        static bool HasOnlyLetters(const std::string& word);
        static bool CanBeFormedFromLetters(const std::string& word, const std::string& availableLetters);

    public:
        WordValidationResult Validate(
            const std::string& word,
            const std::string& availableLetters,
            const std::unordered_set<std::string>& usedWords,
            const Dictionary& dictionary) const;
    };
}