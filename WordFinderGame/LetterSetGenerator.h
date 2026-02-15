#pragma once

#include <string>
#include <random>

namespace WordFinderGame
{
    class LetterSetGenerator
    {

    private:
        std::mt19937 m_rng;

    public:

        LetterSetGenerator();

        explicit LetterSetGenerator(unsigned int seed);

        std::string Generate(size_t letterCount);
    };
}