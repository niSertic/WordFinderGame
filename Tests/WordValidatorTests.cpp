#include "CppUnitTest.h"
#include "../WordFinderGame/WordValidator.h"
#include "../WordFinderGame/Dictionary.h"

#include <unordered_set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace WordFinderGameTests
{

    TEST_CLASS(WordValidatorTests)
    {
    private:
        Dictionary CreateDictionary()
        {
            std::stringstream ss;
            ss << "apple\n"
                << "banana\n"
                << "orange\n";

            Dictionary dict;
            dict.Load(ss);
            return dict;
        }

    public:

        TEST_METHOD(Validate_ReturnsTooShort_WhenWordLengthLessThanThree)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords;
            std::string letters = "abcdefg";

            auto result = validator.Validate("at", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::TooShort, result);
        }

        TEST_METHOD(Validate_ReturnsInvalidCharacters_WhenWordContainsNonLetters)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords;
            std::string letters = "applexyz";

            auto result = validator.Validate("app!e", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::InvalidCharacters, result);
        }

        TEST_METHOD(Validate_ReturnsNotInDictionary_WhenWordIsUnknown)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords;
            std::string letters = "unknownxyz";

            auto result = validator.Validate("unknown", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::NotInDictionary, result);
        }

        TEST_METHOD(Validate_ReturnsAlreadyUsed_WhenWordWasUsedBefore)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords = { "apple" };
            std::string letters = "applexyz";

            auto result = validator.Validate("apple", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::AlreadyUsed, result);
        }

        TEST_METHOD(Validate_ReturnsCannotBeFormedFromLetters_WhenLettersAreInsufficient)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords;
            std::string letters = "aplexyz";

            auto result = validator.Validate("apple", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::CannotBeFormedFromLetters, result);
        }

        TEST_METHOD(Validate_ReturnsValid_ForCorrectWord)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords;
            std::string letters = "applexyz";

            auto result = validator.Validate("apple", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::Valid, result);
        }

        TEST_METHOD(Validate_NormalizesInputToLowercase)
        {
            WordValidator validator;
            Dictionary dict = CreateDictionary();

            std::unordered_set<std::string> usedWords;
            std::string letters = "applexyz";

            auto result = validator.Validate("Apple", letters, usedWords, dict);

            Assert::AreEqual(WordValidationResult::Valid, result);
        }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework
{

    template<>
    std::wstring ToString<WordFinderGame::WordValidationResult>(const WordFinderGame::WordValidationResult& value)
    {
        using WordFinderGame::WordValidationResult;
        switch (value)
        {
        case WordValidationResult::Valid:
            return L"Valid";
        case WordValidationResult::TooShort:
            return L"TooShort";
        case WordValidationResult::InvalidCharacters:
            return L"InvalidCharacters";
        case WordValidationResult::NotInDictionary:
            return L"NotInDictionary";
        case WordValidationResult::AlreadyUsed:
            return L"AlreadyUsed";
        case WordValidationResult::CannotBeFormedFromLetters:
            return L"CannotBeFormedFromLetters";
        default:
            return L"<Unknown WordValidationResult>";
        }
    }
}