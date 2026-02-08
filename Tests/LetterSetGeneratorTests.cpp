#include "CppUnitTest.h"
#include "../WordfinderGame/LetterSetGenerator.h"

#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace WordFinderGameTests
{
    bool IsVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    size_t CountVowels(const std::string& letters)
    {
        return std::count_if(letters.begin(), letters.end(), IsVowel);
    }


    TEST_CLASS(LetterSetGeneratorTests)
    {
    public:

        TEST_METHOD(Generate_ReturnsCorrectLength)
        {
            LetterSetGenerator generator(42);

            const size_t letterCount = 9;
            std::string letters = generator.Generate(letterCount);

            Assert::AreEqual(letterCount, letters.size());
        }

        TEST_METHOD(Generate_ContainsMinimumNumberOfVowels)
        {
            LetterSetGenerator generator(42);

            const size_t letterCount = 9;
            std::string letters = generator.Generate(letterCount);

            const size_t vowelCount = CountVowels(letters);

            Assert::IsTrue(vowelCount >= 3);
        }

        TEST_METHOD(Generate_ContainsOnlyLowercaseLetters)
        {
            LetterSetGenerator generator(42);

            std::string letters = generator.Generate(9);

            bool allLowercase = std::all_of(
                letters.begin(),
                letters.end(),
                [](char c)
                {
                    return c >= 'a' && c <= 'z';
                });

            Assert::IsTrue(allLowercase);
        }

        TEST_METHOD(Generate_FixedSeed_SameLetters)
        {
            LetterSetGenerator gen1(123);
            LetterSetGenerator gen2(123);

            std::string letters1 = gen1.Generate(9);
            std::string letters2 = gen2.Generate(9);

            Assert::AreEqual(letters1, letters2);
        }

        TEST_METHOD(Generate_DifferentSeeds_DifferentLetters)
        {
            LetterSetGenerator gen1(1);
            LetterSetGenerator gen2(2);

            std::string letters1 = gen1.Generate(9);
            std::string letters2 = gen2.Generate(9);

            Assert::AreNotEqual(letters1, letters2);
        }
    };
}