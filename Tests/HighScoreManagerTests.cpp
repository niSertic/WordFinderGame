#include "CppUnitTest.h"
#include "../WordFinderGame/HighScoreManager.h"

#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace WordFinderGameTests
{
    void DeleteFileIfExists(const std::string& path)
    {
        std::remove(path.c_str());
    }

    TEST_CLASS(HighScoreManagerTests)
    {
    public:

        TEST_METHOD(Load_ReturnsEmpty_WhenFileDoesNotExist)
        {
            const std::string filePath = "test_highscores_missing.txt";
            DeleteFileIfExists(filePath);

            HighScoreManager manager(filePath, 5);

            auto scores = manager.Load();

            Assert::AreEqual(static_cast<size_t>(0), scores.size());
        }

        TEST_METHOD(SaveAndLoad_ReturnsSameEntries)
        {
            const std::string filePath = "test_highscores.txt";
            DeleteFileIfExists(filePath);

            HighScoreManager manager(filePath, 10);

            std::vector<HighScoreEntry> original{
                { "Alice", 300, "2026-02-08 10:00" },
                { "Bob",   250, "2026-02-08 10:05" }
            };

            manager.Save(original);

            auto loaded = manager.Load();

            Assert::AreEqual(original.size(), loaded.size());
            Assert::AreEqual(std::string("Alice"), loaded[0].playerName);
            Assert::AreEqual(300, loaded[0].score);
            Assert::AreEqual(std::string("2026-02-08 10:00"), loaded[0].timestamp);

            Assert::AreEqual(std::string("Bob"), loaded[1].playerName);
            Assert::AreEqual(250, loaded[1].score);
            Assert::AreEqual(std::string("2026-02-08 10:05"), loaded[1].timestamp);
        }

        TEST_METHOD(AddNewScore_KeepsHighestScoresOnly)
        {
            const std::string filePath = "test_highscores_addnew.txt";
            DeleteFileIfExists(filePath);

            HighScoreManager manager(filePath, 3);

            std::vector<HighScoreEntry> initial{
                { "Alice",   300, "2026-02-08 10:00" },
                { "Bob",     250, "2026-02-08 10:05" },
                { "Charlie", 200, "2026-02-08 10:10" }
            };
           
            manager.Save(initial);

            HighScoreEntry newEntry{ "Jane", 320, "2026-02-08 10:15" };

            auto updated = manager.AddNewScore(newEntry);

            Assert::AreEqual(static_cast<size_t>(3), updated.size());

            Assert::AreEqual(std::string("Jane"), updated[0].playerName);
            Assert::AreEqual(320, updated[0].score);

            Assert::IsTrue(updated[1].score >= updated[2].score);

            bool hasCharlie = false;
            for (const auto& entry : updated)
            {
                if (entry.playerName == "Charlie")
                {
                    hasCharlie = true;
                    break;
                }
            }

            Assert::IsFalse(hasCharlie);
        }

        TEST_METHOD(QualifiesForHighScore_ReturnsTrue_WhenTableNotFull)
        {
            const std::string filePath = "test_highscores_qualifies1.txt";
            DeleteFileIfExists(filePath);

            HighScoreManager manager(filePath, 5);

            std::vector<HighScoreEntry> initial{
                { "Alice", 300, "2026-02-08 10:00" }
            };

            manager.Save(initial);

            Assert::IsTrue(manager.QualifiesForHighScore(100));
        }

        TEST_METHOD(QualifiesForHighScore_ReturnsTrue_WhenScoreHigherThanExisting)
        {
            const std::string filePath = "test_highscores_qualifies2.txt";
            DeleteFileIfExists(filePath);

            HighScoreManager manager(filePath, 2);

            std::vector<HighScoreEntry> initial{
                { "Alice", 300, "2026-02-08 10:00" },
                { "Bob",   200, "2026-02-08 10:05" }
            };

            manager.Save(initial);

            Assert::IsTrue(manager.QualifiesForHighScore(250));
        }

        TEST_METHOD(QualifiesForHighScore_ReturnsFalse_WhenScoreTooLow)
        {
            const std::string filePath = "test_highscores_qualifies3.txt";
            DeleteFileIfExists(filePath);

            HighScoreManager manager(filePath, 2);

            std::vector<HighScoreEntry> initial{
                { "Alice", 300, "2026-02-08 10:00" },
                { "Bob",   200, "2026-02-08 10:05" }
            };

            manager.Save(initial);

            Assert::IsFalse(manager.QualifiesForHighScore(150));
        }

    };
}