//
// Created by zowlyfon on 21/11/2020.
//

#include "Engine.h"

Engine::Engine(int width, int height) :
screenWidth(width), screenHeight(height), window(nullptr)
{

}

Engine::~Engine()
{
};

void Engine::init()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);

    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gui = new GUI();
    gui->init(window);

    gameLevels.push_back(std::make_shared<GasGiantLevel>(window, gui));
    gameLevels.push_back(std::make_shared<LargePlanetLevel>(window, gui));
    gameLevels.push_back(std::make_shared<SmallPlanetLevel>(window, gui));
    //gameLevels.push_back(std::make_shared<AsteroidLevel>(window, gui));

    activeGameLevel = gameLevels.back();
    gameLevels.pop_back();

    activeGameLevel->init();
}

void Engine::render()
{
    glfwPollEvents();

    glfwSwapBuffers(window);

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::run()
{
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        //physics();

        activeGameLevel->run();

        render();

        if (activeGameLevel->endCond()) {
            if (gameLevels.empty()) {
                glfwSetWindowShouldClose(window, true);
            } else {
                activeGameLevel = gameLevels.back();
                gameLevels.pop_back();

                activeGameLevel->init();
            }
        }
    }
}

void Engine::frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    GameSettings::screenWidth = (float)width;
    GameSettings::screenHeight = (float)height;
}

void Engine::processInput(GLFWwindow *_window)
{
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        paused = !paused;
    }
}