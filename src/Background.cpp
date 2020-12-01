//
// Created by zowlyfon on 26/11/2020.
//

#include "Background.h"

Background::Background(Shader *shader) : playerPos(glm::vec3(0.0f))
{
    RenderObject::shader = shader;
}

Background::~Background()=default;

void Background::init()
{

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bVertices), bVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bIndices), bIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Background::draw(float playerSize)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glUseProgram(shader->getShaderProgram());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(glm::vec2(playerPos / playerSize), -10.0f));
    model = glm::scale(model, glm::vec3(100.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader->getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "playerPos"), 1, glm::value_ptr(playerPos));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
