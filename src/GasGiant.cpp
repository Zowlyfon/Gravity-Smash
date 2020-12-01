//
// Created by zowlyfon on 01/12/2020.
//

#include "GasGiant.h"

GasGiant::GasGiant(Shader *shader, unsigned int subs)
{
    IcoSphere::subs = subs;
    RenderObject::shader = shader;
    RenderObject::computeShader = nullptr;
}

GasGiant::~GasGiant()
=default;

void GasGiant::draw(float scaleFactor)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, RenderObject::position / scaleFactor);
    model = glm::scale(model, glm::vec3(RenderObject::scale / scaleFactor));
    model = glm::rotate(model, glm::radians(rotStep * (GLfloat)glfwGetTime()), rotAxis);

    glm::vec3 objPos = RenderObject::position / scaleFactor;

    auto offset2 = offset + glm::vec3(glfwGetTime()) / 10.0f;

    glUseProgram(shader->getShaderProgram());
    shader->setMat4("model", &model);
    shader->setVec3("modelColor", &color);
    shader->setVec3("offset", &offset2);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}