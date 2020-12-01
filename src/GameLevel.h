//
// Created by zowlyfon on 28/11/2020.
//

#ifndef GAMEENGINE_GAMELEVEL_H
#define GAMEENGINE_GAMELEVEL_H

#include "GameObject.h"
#include "GameSettings.h"
#include "Physics.h"
#include "Background.h"
#include "GUI.h"

class GameLevel {
public:
    GameLevel(GLFWwindow *window);
    ~GameLevel();
    virtual void init();
    virtual bool endCond();
    virtual void run();
    virtual void physics();
    virtual void draw();
    virtual void end();

    virtual void addNewGameObject();
    virtual void processInput(GLFWwindow *window);

    GLFWwindow *window;

    std::shared_ptr<GameObject> player;
    std::vector<std::shared_ptr<GameObject>> worldObjects;

    Shader *shader;
    ComputeShader *computeShader;

    Shader *backgroundShader;

    float prevScaleDivisor;

    GLdouble prevTime;
    GLdouble time;

    Background *background;

    GUI *gui;

    glm::vec3 offset;
};


#endif //GAMEENGINE_GAMELEVEL_H
