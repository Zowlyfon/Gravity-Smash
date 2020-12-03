//
// Created by zowlyfon on 02/12/2020.
//

#ifndef GAMEENGINE_LARGEPLANETLEVEL_H
#define GAMEENGINE_LARGEPLANETLEVEL_H

#include "GameLevel.h"
#include "LargePlanet.h"

class LargePlanetLevel : public GameLevel {
public:
    LargePlanetLevel(GLFWwindow *window, GUI *gui);
    ~LargePlanetLevel();

    void init() override;
    void run() override;
    void draw() override;
    bool endCond() override;
    void end() override;

    void addNewGameObject() override;

    Shader *oceanShader;
};


#endif //GAMEENGINE_LARGEPLANETLEVEL_H
