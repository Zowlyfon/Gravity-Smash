//
// Created by zowlyfon on 26/11/2020.
//

#include "GUI.h"

GUI::GUI() : prevtime(glfwGetTime()), numFrames(0), fps(0)
{

}

GUI::~GUI()
{

}

void GUI::init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void GUI::startFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::drawStats(std::shared_ptr<PhysicsObject> player)
{
    GLdouble time = glfwGetTime();
    GLdouble deltaT = time - prevtime;
    numFrames++;

    if (deltaT >= 1.0f) {
        fps = (float)numFrames;
        numFrames = 0;
        prevtime = time;
    }

    {
        ImGui::Begin("Stats");
        ImGui::Text("Mass: %.1f", player->mass);
        ImGui::Text("Scale: %.2f", player->scale);
        ImGui::Text("Position: %.2f, %.2f",
                    player->position.x,
                    player->position.y);

        ImGui::Text("Velocity: %.2f, %.2f",
                    player->velocity.x,
                    player->velocity.y);
        ImGui::Text("Difficulty: %.2f", GameSettings::difficulty);
        ImGui::Text("FPS: %.0f", fps);
        ImGui::End();
    }
}

void GUI::endFrame()
{
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}