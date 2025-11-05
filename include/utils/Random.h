#pragma once

#include <random>

namespace RPG {

class Random {
public:
    static Random& getInstance();

    int getInt(int min, int max);
    float getFloat(float min, float max);
    bool chance(float probability);

private:
    Random();
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    std::random_device rd;
    std::mt19937 gen;
};

} // namespace RPG
