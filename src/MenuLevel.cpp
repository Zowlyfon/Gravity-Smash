//
// Created by zowlyfon on 01/12/2020.
//

#include "MenuLevel.h"

MenuLevel::MenuLevel(GLFWwindow *window, GUI *gui, std::vector<std::shared_ptr<GameLevel>> &gameLevels) :
GameLevel(window, gui), startGame(false), gameLevels(gameLevels)
{

}

MenuLevel::~MenuLevel()
= default;

void MenuLevel::init()
{
    initLevel();
}

void MenuLevel::run()
{
    runLevel();
}

void MenuLevel::draw()
{
    {
        ImGui::Begin("Menu");
        if (ImGui::Button("Start")) {
            gameLevels.push_back(std::make_shared<MenuLevel>(window, gui, gameLevels));
            gameLevels.push_back(std::make_shared<GasGiantLevel>(window, gui));
            gameLevels.push_back(std::make_shared<LargePlanetLevel>(window, gui));
            //gameLevels.push_back(std::make_shared<SmallPlanetLevel>(window, gui));
            //gameLevels.push_back(std::make_shared<AsteroidLevel>(window, gui));
            startGame = true;
        }
        ImGui::SliderFloat("Gravity",
                           &GameSettings::gravityConstant,
                           0.01f,
                           5.0f);
        ImGui::SliderFloat("Player Speed",
                           &GameSettings::playerSpeed,
                           0.01f,
                           100.0f);
        ImGui::SliderFloat("Level Length",
                           &GameSettings::levelLength,
                           0.01f,
                           10.0f);
        ImGui::SliderFloat("Mass Gain",
                           &GameSettings::massGain,
                           0.01f,
                           10.0f);
        ImGui::SliderFloat("Difficulty",
                           &GameSettings::difficulty,
                           -0.89f,
                           0.09f);
        ImGui::End();
    }
}

bool MenuLevel::endCond()
{
    return startGame;
}

void MenuLevel::end()
{

}

void MenuLevel::processInput(GLFWwindow *window)
{

}