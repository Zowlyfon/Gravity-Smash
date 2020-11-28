//
// Created by zowlyfon on 21/11/2020.
//

#include "RenderObject.h"

RenderObject::RenderObject() :
position(glm::vec3(0.0f)), color(glm::vec3(0.5f)), scale(1.0f),
VAO(0), VBO(0), EBO(0)
{

}

RenderObject::~RenderObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    indices.clear();
    vertices.clear();
}

void RenderObject::init()
{

}

void RenderObject::draw(float playerSize)
{

}

void RenderObject::calculateNormals()
{
    normals.clear();
    normals.resize(vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
        normals[i] = glm::vec3(0.0f);
    }



    for (int i = 0; i < indices.size(); i += 3) {
        auto A = glm::vec3(vertices[indices[i]]);
        auto B = glm::vec3(vertices[indices[i + 1]]);
        auto C = glm::vec3(vertices[indices[i + 2]]);

        glm::vec3 *An = &normals[indices[i]];
        glm::vec3 *Bn = &normals[indices[i + 1]];
        glm::vec3 *Cn = &normals[indices[i + 2]];

        glm::vec3 p = glm::cross(B - A, C - A);

        *An += p;
        *Bn += p;
        *Cn += p;
    }


    for (auto &normal : normals) {
        normal = glm::normalize(normal);
    }
}

void RenderObject::initBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferStorage(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4) + normals.size() * sizeof(glm::vec3), nullptr, GL_DYNAMIC_STORAGE_BIT);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), &vertices.front());
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), normals.size() * sizeof(glm::vec3), &normals.front());

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(vertices.size() * sizeof(glm::vec4)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}