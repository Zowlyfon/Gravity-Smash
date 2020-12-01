//
// Created by zowlyfon on 21/11/2020.
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <vector>
#include <algorithm>
#include <execution>
#include <memory>

#include "GameObject.h"
#include "Asteroid.h"
#include "Utility.h"
#include "Shader.h"
#include "Physics.h"
#include "Background.h"
#include "GUI.h"
#include "GameLevel.h"
#include "AsteroidLevel.h"
#include "GameSettings.h"

class Engine {
public:
    Engine(int width, int height);
    ~Engine();

    void init();
    void render();
    void run();

private:
    static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
    void processInput(GLFWwindow *window);

    GameSettings gameSettings;

    GLFWwindow *window;

    int screenWidth;
    int screenHeight;

    bool paused;

    GameLevel *activeGameLevel;
};


#endif //GAMEENGINE_ENGINE_H
