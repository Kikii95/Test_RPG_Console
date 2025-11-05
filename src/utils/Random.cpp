#include "utils/Random.h"

namespace RPG {

Random::Random() : gen(rd()) {}

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

int Random::getInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<> dist(min, max);
    return static_cast<float>(dist(gen));
}

bool Random::chance(float probability) {
    return getFloat(0.0f, 1.0f) <= probability;
}

} // namespace RPG
