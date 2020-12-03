//
// Created by zowlyfon on 28/11/2020.
//

#ifndef GAMEENGINE_GAMELEVEL_H
#define GAMEENGINE_GAMELEVEL_H

#include "GameObject.h"
#include "GameEffect.h"
#include "GameSettings.h"
#include "Physics.h"
#include "Background.h"
#include "GUI.h"

class GameLevel {
public:
    GameLevel(GLFWwindow *window, GUI *gui);
    ~GameLevel();
    void initLevel();
    void runLevel();
    void drawLevel();
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
    std::vector<std::shared_ptr<GameEffect>> worldEffects;

    Shader *shader;
    ComputeShader *computeShader;

    Shader *effectShader;
    ComputeShader *effectComputeShader;

    Shader *backgroundShader;

    float prevScaleDivisor;

    GLdouble prevTime;
    GLdouble time;

    Background *background;

    GUI *gui;

    glm::vec3 offset;

    GLdouble startTime;

    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 lightPos;
};


#endif //GAMEENGINE_GAMELEVEL_H
