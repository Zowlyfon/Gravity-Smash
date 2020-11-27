//
// Created by zowlyfon on 21/11/2020.
//

#include "Utility.h"

float Utility::randF()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
    auto rand = std::bind(distribution, generator);
    float random = rand();
    return random;
}

float Utility::randF2()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    auto rand = std::bind(distribution, generator);
    float random = rand();
    return random;
}

float Utility::bias(float x, float bias)
{
    float k = pow(1 - bias, 3);
    return (x * k) / (x * k - x + 1);
}