//
// Created by zowlyfon on 21/11/2020.
//

#include "Engine.h"

Engine::Engine(int width, int height) :
screenWidth(width), screenHeight(height), prevTime(0), window(nullptr),
shader(nullptr), player(nullptr), paused(false), prevScaleDivisor(0.0f)
{

}

Engine::~Engine()
{
    delete shader;
};

void Engine::init()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    shader = new Shader("asteroid.vert.glsl",
                        "asteroid.frag.glsl");

    backgroundShader = new Shader("background.vert.glsl",
                                  "background.frag.glsl");

    std::cout << "Shaders Loaded" << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    std::shared_ptr<PhysicsObject> playerSphere(new Sphere(256.0f, 128.0f, 6));
    player = playerSphere;

    player->color = glm::vec3(0.15f, 0.14f, 0.14f);
    player->mass = 1.0f;
    player->scale = Physics::scaleFromMass(50);
    player->position = glm::vec3(0.0f, 0.0f, 0.0f);

    player->init();

    worldObjects.push_back(playerSphere);

    std::vector<glm::vec3> spherePositions;

    for(int i = 0; i < 256; i++) {
        createRandomSphere();
    }

    background = new Background();
    background->init();

    gui = new GUI();
    gui->init(window);

    offset = glm::vec3(Utility::randF(), Utility::randF(), Utility::randF());
}

void Engine::physics()
{
    auto time = glfwGetTime();

    Physics::calculateGravity(&worldObjects, player, prevTime, time);

    Physics::calculateCollisions(&worldObjects, player);

    for (const auto &object : worldObjects) {
        object->physics();
    }

    Physics::calculateOutOfRange(&worldObjects, player);

    /* Delete destroyed objects */
    worldObjects.erase(
      std::remove_if(
        worldObjects.begin(),
        worldObjects.end(),
        [=](auto &&object) {
            return (object->dead || (object->scale < player->scale / 32.0f));
        }),
        worldObjects.end()
      );


    /* Randomly add new objects */
    GLfloat random = Utility::randF2();

    if (random > 0.95 && worldObjects.size() < 256) {
        createRandomSphere();
        if (worldObjects.size() < 128) {
            createRandomSphere();
        }
    }

    for (const auto &object : worldObjects) {
        object->scale = Physics::scaleFromMass(object->mass);
    }
}

void Engine::render()
{
    glfwPollEvents();

    float scaleDivisor;

    if (prevScaleDivisor < player->baseSize &&
    prevScaleDivisor + player->baseSize / 100.0f < player->baseSize) {
        scaleDivisor = prevScaleDivisor + player->baseSize / 100.0f;
    } else if (prevScaleDivisor > player->baseSize &&
    prevScaleDivisor - player->baseSize / 100.0f > player->baseSize) {
        scaleDivisor = prevScaleDivisor - player->baseSize / 100.0f;
    } else {
        scaleDivisor = player->baseSize;
    }

    prevScaleDivisor = scaleDivisor;

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(
      glm::radians(45.0f),
      (float)screenWidth / (float)screenHeight,
      0.1f,
      100.0f);

    //glm::vec3 cameraPos = glm::vec3(player->position.x, player->position.y, player->scale * 15.0f + 15.0f);
    glm::vec3 cameraPos = glm::vec3(player->position.x / scaleDivisor, player->position.y / scaleDivisor, 25.0f);

    view = glm::lookAt(cameraPos,
                       player->position / scaleDivisor,
                       glm::vec3(0.0f, 1.0f, 0.0f));

    /* Draw Background */

    glm::vec3 offset2 = offset + (float)glfwGetTime() / 10.0f;

    glUseProgram(backgroundShader->getShaderProgram());

    glUniformMatrix4fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "offset"), 1, glm::value_ptr(offset2));

    background->playerPos = player->position;
    background->draw(backgroundShader, scaleDivisor);

    /* Render Objects */

    glUseProgram(shader->getShaderProgram());

    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "viewPos"), 1, glm::value_ptr(cameraPos));

    glUniformMatrix4fv(glGetUniformLocation(shader->getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader->getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::vec3 lightPos = glm::vec3(player->position.x / scaleDivisor, player->position.y / scaleDivisor, 5.0f);
    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform1f(glGetUniformLocation(shader->getShaderProgram(), "playerScale"), player->scale);

    //glm::mat4 model = glm::mat4(1.0f);
    //glUniformMatrix4fv(glGetUniformLocation(shader->getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    for (auto const &object : worldObjects) {
        object->draw(shader, scaleDivisor);
    }

    /* Draw GUI */
    gui->draw(player);

    prevTime = glfwGetTime();
    glfwSwapBuffers(window);
}

void Engine::run()
{
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        physics();

        render();
    }
}

void Engine::frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Engine::processInput(GLFWwindow *window)
{
    GLfloat step = player->scale * 0.1;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player->velocity.y += step;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player->velocity.x -= step;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player->velocity.y -= step;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player->velocity.x += step;
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        paused = !paused;
    }
}

void Engine::createRandomSphere()
{
    std::shared_ptr<PhysicsObject> sphere(new Sphere(128.0f, 64.0f));
    /*
    sphere->color = glm::vec3(Utility::randF2(),
                              Utility::randF2(),
                              Utility::randF2());
                              */
    sphere->color = glm::vec3(0.15f, 0.14f, 0.14f);
    sphere->color += glm::vec3(Utility::randF() / 20.0f,
                               Utility::randF() / 100.0f,
                               Utility::randF() / 100.0f);

    sphere->mass = (Utility::bias(Utility::randF2(), 0.9f)) * player->mass * 200.0f + player->mass / 16;
    sphere->scale = Physics::scaleFromMass(sphere->mass);
    sphere->position = glm::vec3(Utility::randF() * sphere->scale * 100.0f + player->position.x,
                                 Utility::randF() * sphere->scale * 100.0f + player->position.y,
                                 0.0f);

    sphere->velocity = glm::vec3(Utility::randF() / (sphere->scale * 4),
                                 Utility::randF() / (sphere->scale * 4),
                                 0.0f);

    sphere->init();

    worldObjects.push_back(sphere);
}