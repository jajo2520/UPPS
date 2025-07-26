#pragma once
#include <random>
#include <chrono>

class RNG
{
private:
public:
    RNG() {};
    int randInt(int lower, int upper)
    {
        std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		    std::chrono::steady_clock::now().time_since_epoch().count()
		) };
        std::uniform_int_distribution dist{lower, upper};
        return dist(mt);
        // code shamelessly yanked from the internet
    }
};
