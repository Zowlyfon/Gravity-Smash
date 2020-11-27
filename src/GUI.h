//
// Created by zowlyfon on 26/11/2020.
//

#ifndef GAMEENGINE_GUI_H
#define GAMEENGINE_GUI_H

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "PhysicsObject.h"

class GUI {
public:
    GUI();
    ~GUI();
    void init(GLFWwindow *window);
    void draw(std::shared_ptr<PhysicsObject> player);
private:
    GLdouble prevtime;
    unsigned int numFrames;
    float fps;
};


#endif //GAMEENGINE_GUI_H
