//
// Created by zowlyfon on 27/11/2020.
//

#include "Atmosphere.h"

Atmosphere::Atmosphere(std::shared_ptr<Shader> newShader)
{
    shader = newShader;
}

Atmosphere::~Atmosphere()=default;

void Atmosphere::init()
{
    subs = 3;

    createIcosahedron();

    for (int i = 0; i < subs; i++) {
        subdivideMesh();
    }

    originalVertices = vertices;

    initBuffers();
}

void Atmosphere::draw(float playerSize)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position / playerSize);
    model = glm::scale(model, glm::vec3(scale / playerSize));

    glm::vec3 objPos = position / playerSize;

    shader->setMat4("model", &model);
}