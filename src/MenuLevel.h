//
// Created by zowlyfon on 01/12/2020.
//

#ifndef GAMEENGINE_MENULEVEL_H
#define GAMEENGINE_MENULEVEL_H

#include "GameLevel.h"
#include "AsteroidLevel.h"
#include "SmallPlanetLevel.h"
#include "LargePlanetLevel.h"
#include "GasGiantLevel.h"

class MenuLevel : public GameLevel {
public:
    MenuLevel(GLFWwindow *window, GUI *gui, std::vector<std::shared_ptr<GameLevel>> &gameLevels);
    ~MenuLevel();

    void init() override;
    void run() override;
    void draw() override;
    bool endCond() override;
    void end() override;
    void processInput(GLFWwindow *window) override;

private:
    bool startGame;
    std::vector<std::shared_ptr<GameLevel>> &gameLevels;
};


#endif //GAMEENGINE_MENULEVEL_H
