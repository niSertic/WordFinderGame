#pragma once

#include <string>
#include <random>

namespace WordFinderGame
{
    class LetterSetGenerator
    {

    private:
        std::mt19937 m_rng;

        static constexpr char VOWELS[] = { 'a', 'e', 'i', 'o', 'u' };
        static constexpr char CONSONANTS[] = {
            'b','c','d','f','g','h','j','k','l','m',
            'n','p','q','r','s','t','v','w','x','y','z'
        };

        static bool IsVowel(char c);

    public:

        LetterSetGenerator();

        explicit LetterSetGenerator(unsigned int seed);

        std::string Generate(size_t letterCount);
    };
}