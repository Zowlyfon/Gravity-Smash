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

    /*
    shader = std::make_shared<Shader>("asteroid.vert.glsl",
                                      "asteroid.frag.glsl");

    backgroundShader = std::make_shared<Shader>("background.vert.glsl",
                                                "background.frag.glsl");

    computeShader = std::make_shared<ComputeShader>("asteroidNoise.comp.glsl");
    */

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Implemented in Level
    std::shared_ptr<GameObject> playerSphere(new Asteroid(6));
    player = playerSphere;

    player->shader = shader;
    player->computeShader = computeShader;

    player->color = glm::vec3(0.15f, 0.14f, 0.14f);
    player->mass = 1.0f;
    player->PhysicsObject::scale = Physics::scaleFromMass(50);
    player->PhysicsObject::position = glm::vec3(0.0f, 0.0f, 0.0f);

    player->init();

    worldObjects.push_back(playerSphere);

    for(int i = 0; i < GameSettings::maxObjects; i++) {
        createRandomSphere();
    }
    */

    gui = new GUI();
    gui->init(window);

    gameLevels.push_back(std::make_shared<GasGiantLevel>(window, gui));
    //gameLevels.push_back(std::make_shared<SmallPlanetLevel>(window, gui));
    //gameLevels.push_back(std::make_shared<AsteroidLevel>(window, gui));

    activeGameLevel = gameLevels.back();
    gameLevels.pop_back();

    activeGameLevel->init();

    /*
    background = new Background();
    background->shader = backgroundShader;
    background->init();

    gui = new GUI();
    gui->init(window);

    offset = glm::vec3(Utility::randF(), Utility::randF(), Utility::randF());
    */
}

/*
void Engine::physics()
{
    auto time = glfwGetTime();

    Physics::calculateGravity(worldObjects, player, prevTime, time);

    Physics::calculateCollisions(worldObjects, player);

    for (const auto &object : worldObjects) {
        object->physics();
    }

    Physics::calculateOutOfRange(worldObjects, player);
    */
    /* Delete destroyed objects */
    /*
    worldObjects.erase(
      std::remove_if(
        worldObjects.begin(),
        worldObjects.end(),
        [=](auto &&object) {
            return (object->dead || (object->PhysicsObject::scale < player->PhysicsObject::scale / 32.0f));
        }),
        worldObjects.end()
      );

    */
    /* Randomly add new objects */
    /*
    GLfloat random = Utility::randF2();

    if (random > 0.95 && worldObjects.size() < gameSettings.maxObjects) {
        createRandomSphere();
        if (worldObjects.size() < gameSettings.maxObjects / 2) {
            createRandomSphere();
        }
    }


    for (const auto &object : worldObjects) {
        object->PhysicsObject::scale = Physics::scaleFromMass(object->mass);
    }
}
*/

void Engine::render()
{
    glfwPollEvents();

    /*
    float scaleFactor;

    if (prevScaleDivisor < player->baseSize &&
    prevScaleDivisor + player->baseSize / 100.0f <= player->baseSize) {
        scaleFactor = prevScaleDivisor + player->baseSize / 100.0f;
    } else if (prevScaleDivisor > player->baseSize &&
    prevScaleDivisor - player->baseSize / 100.0f >= player->baseSize) {
        scaleFactor = prevScaleDivisor - player->baseSize / 100.0f;
    } else {
        scaleFactor = player->baseSize;
    }

    prevScaleDivisor = scaleFactor;

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(
      glm::radians(45.0f),
      (float)screenWidth / (float)screenHeight,
      0.1f,
      100.0f);

    glm::vec3 cameraPos = glm::vec3(player->RenderObject::position.x / scaleFactor, player->RenderObject::position.y / scaleFactor, 25.0f);

    view = glm::lookAt(cameraPos,
                       player->RenderObject::position / scaleFactor,
                       glm::vec3(0.0f, 1.0f, 0.0f));
    */
    /* Draw Background */
    /*
    glm::vec3 offset2 = offset + (float)glfwGetTime() / 10.0f;

    glUseProgram(backgroundShader->getShaderProgram());

    glUniformMatrix4fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "offset"), 1, glm::value_ptr(offset2));

    glDisable(GL_CULL_FACE);

    background->playerPos = player->RenderObject::position;
    background->draw(scaleFactor);

    glEnable(GL_CULL_FACE);
    */
    /* Render Objects */
    /*
    glm::vec3 lightPos = glm::vec3(player->RenderObject::position.x / scaleFactor, player->RenderObject::position.y / scaleFactor, 5.0f);

    glUseProgram(shader->getShaderProgram());

    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "viewPos"), 1, glm::value_ptr(cameraPos));

    shader->setMat4("projection", &projection);
    shader->setMat4("view", &view);


    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform1f(glGetUniformLocation(shader->getShaderProgram(), "playerScale"), player->RenderObject::scale);



    for (auto const &object : worldObjects) {
        object->draw(scaleFactor);
    }
    */
    /* Draw GUI */
    //gui->draw(player);

    glfwSwapBuffers(window);

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::run()
{
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        activeGameLevel->processInput(window);

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
}

void Engine::processInput(GLFWwindow *_window)
{
    /*
    GLfloat step = player->PhysicsObject::scale * 0.1;

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
    */

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        paused = !paused;
    }
}

/*
void Engine::createRandomSphere()
{

    std::shared_ptr<GameObject> sphere(new Asteroid());
    sphere->shader = shader;
    sphere->computeShader = computeShader;
    sphere->color = glm::vec3(0.15f, 0.14f, 0.14f);
    sphere->color += glm::vec3(Utility::randF() / 20.0f,
                               Utility::randF() / 100.0f,
                               Utility::randF() / 100.0f);

    sphere->mass = (Utility::bias(Utility::randF2(), 0.9f)) * player->mass * 200.0f + player->mass / 16;
    sphere->PhysicsObject::scale = Physics::scaleFromMass(sphere->mass);
    sphere->PhysicsObject::position = glm::vec3(Utility::randF() * sphere->PhysicsObject::scale * 100.0f + player->PhysicsObject::position.x,
                                 Utility::randF() * sphere->PhysicsObject::scale * 100.0f + player->PhysicsObject::position.y,
                                 Utility::randF() * 100.0f);

    sphere->velocity = glm::vec3(Utility::randF() / (sphere->PhysicsObject::scale * 4),
                                 Utility::randF() / (sphere->PhysicsObject::scale * 4),
                                 0.0f);

    sphere->init();

    worldObjects.push_back(sphere);

}
*/