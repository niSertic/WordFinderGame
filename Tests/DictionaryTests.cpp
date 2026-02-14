#include "CppUnitTest.h"
#include "../WordFinderGame/Dictionary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WordFinderGame;

namespace WordFinderGameTests
{

    TEST_CLASS(DictionaryTests)
    {
    private:

        Dictionary CreateDictionary()
        {
            std::stringstream ss;

            ss << "apple\n"
                << "banana\n"
                << "dog\n"
                << "cat\n"
                << "tree\n"
                << "world\n"
                << "football\n"
                << "at\n"              
                << "hi\n"              
                << "it's\n"            
                << "mother-in-law\n"   
                << "123\n"            
                << "hello!\n";       

            Dictionary dict;
            dict.Load(ss);
            return dict;
        }
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
            Dictionary dict = CreateDictionary();

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
            std::stringstream ss;
            ss << "Apple\n";

            Dictionary dict;
            dict.Load(ss);

            Assert::IsTrue(dict.Contains("apple"));
            Assert::IsFalse(dict.Contains("Apple"));
        }

        TEST_METHOD(Size_ReturnsCorrectNumberOfWords)
        {
            Dictionary dict = CreateDictionary();

            Assert::AreEqual(7ull, dict.Size());
        }

        TEST_METHOD(Clear_RemovesAllWords)
        {
            Dictionary dict = CreateDictionary();

            dict.Clear();

            Assert::AreEqual(0ull, dict.Size());
            Assert::IsFalse(dict.Contains("apple"));
        }
    };
}