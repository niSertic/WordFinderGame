#include "LetterSetGenerator.h"

#include <algorithm>
#include <vector>


namespace WordFinderGame
{
    LetterSetGenerator::LetterSetGenerator() : m_rng(std::random_device{}())
    {
    }

    LetterSetGenerator::LetterSetGenerator(unsigned int seed) : m_rng(seed)
    {
    }

    std::string LetterSetGenerator::Generate(size_t letterCount)
    {
        // Generates a random set of lowercase letters.
        // Ensures a minimum number of vowels to avoid unplayable combinations.

        static constexpr char VOWELS[] = { 'a', 'e', 'i', 'o', 'u' };
        static constexpr char CONSONANTS[] = {
            'b','c','d','f','g','h','j','k','l','m',
            'n','p','q','r','s','t','v','w','x','y','z'
        };

        std::vector<char> letters;
        letters.reserve(letterCount);

        const size_t minVowels = std::max<size_t>(2, letterCount / 3);
        const size_t consonantCount = letterCount - minVowels;

        std::uniform_int_distribution<size_t> vowelDist(0, std::size(VOWELS) - 1);
        std::uniform_int_distribution<size_t> consonantDist(0, std::size(CONSONANTS) - 1);

      
        for (size_t i = 0; i < minVowels; ++i)
        {
            letters.push_back(VOWELS[vowelDist(m_rng)]);
        }

   
        for (size_t i = 0; i < consonantCount; ++i)
        {
            letters.push_back(CONSONANTS[consonantDist(m_rng)]);
        }

 
        std::shuffle(letters.begin(), letters.end(), m_rng);

        return std::string(letters.begin(), letters.end());
    }
}