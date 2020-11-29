//
// Created by zowlyfon on 27/11/2020.
//

#include "Atmosphere.h"

Atmosphere::Atmosphere()
{}

Atmosphere::~Atmosphere()=default;

void Atmosphere::init()
{
    subs = 3;

    initIcosphere();
    calculateNormals();
    initBuffers();
}

void Atmosphere::draw(float playerSize)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position / playerSize);
    model = glm::scale(model, glm::vec3(scale / playerSize));
    glm::vec3 objPos = position / playerSize;

    glUseProgram(shader->getShaderProgram());
    shader->setMat4("model", &model);
    shader->setVec3("objPos", &objPos);
    shader->setFloat("objSize", scale / playerSize);
    //shader->setVec3("modelColor", &color);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}