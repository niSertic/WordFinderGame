#include "CppUnitTest.h"
#include "../WordFinderGame/ScoreCalculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace WordFinderGameTests
{
    TEST_CLASS(ScoreCalculatorTests)
    {
    public:

        TEST_METHOD(CalculateScore_Returns10Points_ForThreeLetterWord)
        {
            int score = ScoreCalculator::CalculateScore("abc", "abcdefghi");
            Assert::AreEqual(10, score);
        }

        TEST_METHOD(CalculateScore_Returns20Points_ForFourLetterWord)
        {
            int score = ScoreCalculator::CalculateScore("abcd", "abcdefghi");
            Assert::AreEqual(20, score);
        }

        TEST_METHOD(CalculateScore_Returns30Points_ForFiveLetterWord)
        {
            int score = ScoreCalculator::CalculateScore("abcde", "abcdefghi");
            Assert::AreEqual(30, score);
        }

        TEST_METHOD(CalculateScore_Returns40Points_ForSixLetterWord)
        {
            int score = ScoreCalculator::CalculateScore("abcdef", "abcdefghi");
            Assert::AreEqual(40, score);
        }

        TEST_METHOD(CalculateScore_Returns50Points_ForSevenLetterWord)
        {
            int score = ScoreCalculator::CalculateScore("abcdefg", "abcdefghi");
            Assert::AreEqual(50, score);
        }

        TEST_METHOD(CalculateScore_Returns60Points_ForEightOrMoreLetterWord)
        {
            int score = ScoreCalculator::CalculateScore("abcdefgh", "abcdefghi");
            Assert::AreEqual(60, score);
        }

        TEST_METHOD(CalculateScore_AddsBonus_WhenAllLettersAreUsed)
        {
            int score = ScoreCalculator::CalculateScore("abcdefghi", "abcdefghi");
            Assert::AreEqual(110, score);
        }
    };
}