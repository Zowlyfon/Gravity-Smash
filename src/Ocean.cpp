//
// Created by zowlyfon on 02/12/2020.
//

#include "Ocean.h"

Ocean::Ocean(Shader *shader)
{
    RenderObject::shader = shader;
    RenderObject::computeShader = nullptr;
}

Ocean::~Ocean()
= default;

void Ocean::init()
{
    subs = 4;
    color = glm::vec3(0.0f, 0.2f, 0.5f);
    initIcosphere();
    calculateNormals();
    initBuffers();
}

void Ocean::draw(float scaleFactor)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, *oceanPos / scaleFactor);
    model = glm::scale(model, glm::vec3(*oceanScale / scaleFactor));
    //model = glm::rotate(model, glm::radians(rotStep * (GLfloat)glfwGetTime()), rotAxis);

    glm::vec3 objPos = *oceanPos / scaleFactor;

    glUseProgram(shader->getShaderProgram());
    shader->setMat4("model", &model);
    shader->setVec3("modelColor", &color);
    shader->setVec3("offset", &offset);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}