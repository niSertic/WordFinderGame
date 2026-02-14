#include "CppUnitTest.h"
#include "../WordFinderGame/GameState.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace WordFinderGameTests
{

    TEST_CLASS(GameStateTests)
    {
    public:

        TEST_METHOD(InitialState_IsCorrect)
        {
            GameState state("abcdefghi", 10, std::chrono::seconds(60));

            Assert::AreEqual(std::string("abcdefghi"), state.GetAvailableLetters());
            Assert::AreEqual(0, state.GetScore());
            Assert::AreEqual(0ull, state.GetAttemptsUsed());
            Assert::AreEqual(10ull, state.GetAttemptsRemaining());
            Assert::IsFalse(state.IsGameOver());
        }

        TEST_METHOD(AddWord_IncreasesScore_AndStoresWord)
        {
            GameState state("abcdefghi", 10, std::chrono::seconds(60));

            state.AddWord("cat", 10);

            Assert::AreEqual(10, state.GetScore());
            Assert::IsTrue(state.GetFoundWords().contains("cat"));
        }

        TEST_METHOD(IncrementAttempts_IncreasesAttemptCount)
        {
            GameState state("abcdefghi", 5, std::chrono::seconds(60));

            state.IncrementAttempts();
            state.IncrementAttempts();

            Assert::AreEqual(2ull, state.GetAttemptsUsed());
            Assert::AreEqual(3ull, state.GetAttemptsRemaining());
        }

        TEST_METHOD(IsGameOver_ReturnsTrue_WhenAttemptsExceeded)
        {
            GameState state("abcdefghi", 2, std::chrono::seconds(60));

            state.IncrementAttempts();
            state.IncrementAttempts();

            Assert::IsTrue(state.IsAttemptsExceeded());
            Assert::IsTrue(state.IsGameOver());
        }

        TEST_METHOD(IsGameOver_ReturnsTrue_WhenTimeIsUp)
        {
            using clock = std::chrono::steady_clock;

            auto fakeNow = clock::now();

            GameState state("abcdefghi", 10, std::chrono::seconds(1), [&fakeNow]() { return fakeNow; });

            fakeNow += std::chrono::seconds(2);

            Assert::IsTrue(state.IsTimeUp());
            Assert::IsTrue(state.IsGameOver());
        }

        TEST_METHOD(GetTimeRemaining_NeverReturnsNegative)
        {
            using clock = std::chrono::steady_clock;

            auto fakeNow = clock::now();

            GameState state("abcdefghi", 10, std::chrono::seconds(1), [&fakeNow]() { return fakeNow; });

            fakeNow += std::chrono::seconds(5);

            auto remaining = state.GetTimeRemaining();

            Assert::AreEqual(0ll, remaining.count());
        }
    };
}