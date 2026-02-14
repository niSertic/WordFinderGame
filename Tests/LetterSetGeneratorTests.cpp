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

            const size_t sizes[] = { 5, 7, 9, 12 };

            for (size_t size : sizes)
            {
                std::string letters = generator.Generate(size);
                Assert::AreEqual(size, letters.size());
            }
        }

        TEST_METHOD(Generate_ContainsMinimumNumberOfVowels)
        {
            LetterSetGenerator generator(42);

            const size_t letterCount1 = 9;
            const size_t letterCount2 = 5;
            std::string letters1 = generator.Generate(letterCount1);
            std::string letters2 = generator.Generate(letterCount2);

            const size_t vowelCount1 = CountVowels(letters1);
            const size_t vowelCount2 = CountVowels(letters2);

            Assert::IsTrue(vowelCount1 >= 3);
            Assert::IsTrue(vowelCount2 >= 2);
            Assert::IsFalse(vowelCount2 >= 3);
            
        }

        TEST_METHOD(Generate_ContainsOnlyLowercaseLetters)
        {
            LetterSetGenerator generator(42);

            std::string letters = generator.Generate(15);

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
            std::string letters3 = gen1.Generate(7);
            std::string letters4 = gen2.Generate(7);

            Assert::AreEqual(letters1, letters2);
            Assert::AreEqual(letters3, letters4);
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