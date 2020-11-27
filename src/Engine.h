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

#include "Sphere.h"
#include "PhysicsObject.h"
#include "Utility.h"
#include "Shader.h"
#include "Physics.h"
#include "Background.h"
#include "GUI.h"

class Engine {
public:
    Engine(int width, int height);
    ~Engine();

    void init();
    void physics();
    void render();
    void run();

private:
    static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
    void processInput(GLFWwindow *window);
    void createRandomSphere();

    GLFWwindow *window;

    Shader *shader;
    Shader *backgroundShader;

    std::vector<std::shared_ptr<PhysicsObject>> worldObjects;
    Background *background;

    std::shared_ptr<PhysicsObject> player;

    GLdouble prevTime;

    int screenWidth;
    int screenHeight;

    float prevScaleDivisor;

    bool paused;

    GUI *gui;

    glm::vec3 offset;
};


#endif //GAMEENGINE_ENGINE_H
