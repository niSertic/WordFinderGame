#include "CppUnitTest.h"
#include "../WordFinderGame/GameState.h"

#include <thread>

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
            Assert::AreEqual(static_cast<size_t>(0), state.GetAttemptsUsed());
            Assert::AreEqual(static_cast<size_t>(10), state.GetAttemptsRemaining());
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

            Assert::AreEqual(static_cast<size_t>(2), state.GetAttemptsUsed());
            Assert::AreEqual(static_cast<size_t>(3), state.GetAttemptsRemaining());
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
            GameState state("abcdefghi", 10, std::chrono::seconds(1));

            std::this_thread::sleep_for(std::chrono::seconds(2));

            Assert::IsTrue(state.IsTimeUp());
            Assert::IsTrue(state.IsGameOver());
        }

        TEST_METHOD(GetTimeRemaining_NeverReturnsNegative)
        {
            GameState state("abcdefghi", 10, std::chrono::seconds(1));

            std::this_thread::sleep_for(std::chrono::seconds(2));

            auto remaining = state.GetTimeRemaining();

            Assert::IsTrue(remaining.count() >= 0);
        }
    };
}