//
// Created by zowlyfon on 01/12/2020.
//

#ifndef GAMEENGINE_SMALLPLANETLEVEL_H
#define GAMEENGINE_SMALLPLANETLEVEL_H

#include "GameLevel.h"
#include "SmallPlanet.h"

class SmallPlanetLevel : public GameLevel {
public:
    SmallPlanetLevel(GLFWwindow *window, GUI *gui);
    ~SmallPlanetLevel();

    void init() override;
    void run() override;
    bool endCond() override;
    void end() override;

    void addNewGameObject() override;
};


#endif //GAMEENGINE_SMALLPLANETLEVEL_H
