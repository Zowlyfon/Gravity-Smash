//
// Created by zowlyfon on 26/11/2020.
//
#ifndef GAMEENGINE_BACKGROUND_H
#define GAMEENGINE_BACKGROUND_H

#include "RenderObject.h"

class Background : public RenderObject{
public:
    explicit Background(Shader *shader);
    ~Background();
    void init() override;
    void draw(float playerSize) override;

    glm::vec3 playerPos;

private:
    constexpr static const float bVertices[] = {
      0.5f,  0.5f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left
    };
    constexpr static const unsigned int bIndices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
    };
};


#endif //GAMEENGINE_BACKGROUND_H
