#include "CppUnitTest.h"
#include "../WordFinderGame/Dictionary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace DictionaryTests
{

    TEST_CLASS(DictionaryTests)
    {
    public:

        TEST_METHOD(LoadFromFile_ReturnsFalse_WhenFileDoesNotExist)
        {
            Dictionary dict;

            bool result = dict.LoadFromFile("non_existing_file.txt");

            Assert::IsFalse(result);
            Assert::AreEqual(static_cast<size_t>(0), dict.Size());
        }

        TEST_METHOD(LoadFromFile_LoadsValidWordsOnly)
        {
            Dictionary dict;

            bool result = dict.LoadFromFile("test_dictionary.txt");

            Assert::IsTrue(result);


            Assert::IsTrue(dict.Contains("apple"));
            Assert::IsTrue(dict.Contains("banana"));
            Assert::IsTrue(dict.Contains("dog"));
            Assert::IsTrue(dict.Contains("cat"));
            Assert::IsTrue(dict.Contains("tree"));
            Assert::IsTrue(dict.Contains("world"));
            Assert::IsTrue(dict.Contains("football"));


            Assert::IsFalse(dict.Contains("at"));
            Assert::IsFalse(dict.Contains("hi"));
            Assert::IsFalse(dict.Contains("it's"));
            Assert::IsFalse(dict.Contains("mother-in-law"));
            Assert::IsFalse(dict.Contains("123"));
            Assert::IsFalse(dict.Contains("hello!"));
        }

        TEST_METHOD(Dictionary_NormalizesToLowercase)
        {
            Dictionary dict;
            dict.LoadFromFile("test_dictionary.txt");

            Assert::IsTrue(dict.Contains("apple"));
            Assert::IsFalse(dict.Contains("Apple"));
        }

        TEST_METHOD(Size_ReturnsCorrectNumberOfWords)
        {
            Dictionary dict;
            dict.LoadFromFile("test_dictionary.txt");


            Assert::AreEqual(static_cast<size_t>(7), dict.Size());
        }

        TEST_METHOD(Clear_RemovesAllWords)
        {
            Dictionary dict;
            dict.LoadFromFile("test_dictionary.txt");

            dict.Clear();

            Assert::AreEqual(static_cast<size_t>(0), dict.Size());
            Assert::IsFalse(dict.Contains("apple"));
        }
    };
}