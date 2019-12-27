#ifndef RANDOMH
#define RANDOMH

#include <functional>
#include <random>

inline double RandomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<double()> RandGenerator =
        std::bind(distribution, generator);
    return RandGenerator();
}
#endif