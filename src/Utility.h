//
// Created by zowlyfon on 21/11/2020.
//

#ifndef GAMEENGINE_UTILITY_H
#define GAMEENGINE_UTILITY_H

#include <random>
#include <functional>

class Utility {
public:
    static float randF();
    static float randF2();
    static float bias(float x, float bias);
};


#endif //GAMEENGINE_UTILITY_H
