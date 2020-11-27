//
// Created by zowlyfon on 26/11/2020.
//

#include "GUI.h"

GUI::GUI()
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

void GUI::draw(std::shared_ptr<PhysicsObject> player)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

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
        ImGui::End();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}