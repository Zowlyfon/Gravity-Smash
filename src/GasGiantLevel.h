//
// Created by zowlyfon on 01/12/2020.
//

#ifndef GAMEENGINE_GASGIANTLEVEL_H
#define GAMEENGINE_GASGIANTLEVEL_H

#include "GameLevel.h"
#include "GasGiant.h"

class GasGiantLevel : public GameLevel {
public:
    explicit GasGiantLevel(GLFWwindow *window, GUI *gui);
    ~GasGiantLevel();

    void init() override;
    void run() override;
    bool endCond() override;
    void end() override;

    void addNewGameObject() override;
};


#endif //GAMEENGINE_GASGIANTLEVEL_H
