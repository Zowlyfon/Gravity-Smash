//
// Created by zowlyfon on 29/11/2020.
//

#ifndef GAMEENGINE_ASTEROIDLEVEL_H
#define GAMEENGINE_ASTEROIDLEVEL_H

#include "GameLevel.h"
#include "GameObject.h"
#include "Asteroid.h"
#include "Physics.h"
#include "GameSettings.h"

class AsteroidLevel : public GameLevel {
public:
    AsteroidLevel(GLFWwindow *window);
    ~AsteroidLevel();

    void init() override;
    void run() override;
    bool endCond() override;
    void end() override;

    void addNewGameObject() override;
};


#endif //GAMEENGINE_ASTEROIDLEVEL_H
