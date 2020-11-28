//
// Created by zowlyfon on 27/11/2020.
//

#include "Asteroid.h"

Asteroid::Asteroid(unsigned int subs)
{
    IcoSphere::subs = subs;
}

Asteroid::~Asteroid()=default;

void Asteroid::init()
{
    offset = glm::vec3(Utility::randF() * 100.0f,
                       Utility::randF() * 100.0f,
                       Utility::randF() * 100.0f);

    rotAxis = glm::vec3(Utility::randF(),
                        Utility::randF(),
                        Utility::randF());

    rotStep = Utility::randF() * 30;

    initIcosphere();
    addNoise();
    calculateNormals();
    initBuffers();
}

void Asteroid::physics()
{
    auto time = glfwGetTime();
    GLdouble deltaT = time - prevTime;

    PhysicsObject::position += velocity * (GLfloat)deltaT;
    RenderObject::position = PhysicsObject::position;
    RenderObject::scale = PhysicsObject::scale;

    prevTime = time;
}

void Asteroid::draw(float playerSize)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, RenderObject::position / playerSize);
    model = glm::scale(model, glm::vec3(RenderObject::scale / playerSize));
    model = glm::rotate(model, glm::radians(rotStep * (GLfloat)glfwGetTime()), rotAxis);

    glm::vec3 objPos = RenderObject::position / playerSize;

    shader->setMat4("model", &model);
    shader->setVec3("modelColor", &color);
    shader->setVec3("offset", &offset);
    shader->setVec3("objPos", &objPos);
    shader->setFloat("objScale", RenderObject::scale / playerSize);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Asteroid::addNoise()
{
    ComputeShader computeShader("addSimplexNoise.comp.glsl");


    glUseProgram(computeShader.getShaderProgram());

    GLuint vertexSSBO;
    glGenBuffers(1, &vertexSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertexSSBO);
    //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertexSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_DYNAMIC_COPY);
    glUniform3fv(glGetUniformLocation(computeShader.getShaderProgram(), "offset"), 1, glm::value_ptr(offset));
    glUniform1f(glGetUniformLocation(computeShader.getShaderProgram(), "objScale"), PhysicsObject::scale);
    glDispatchCompute(vertices.size() / 256, 1, 1);

    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertexSSBO);


    glm::vec4 *ptr;
    int numVertices = vertices.size();
    ptr = (glm::vec4 *) glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

    vertices.clear();

    for (int i = 0; i < numVertices; i++) {
        vertices.push_back(ptr[i]);
    }

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void Asteroid::updateMass()
{
    if (PhysicsObject::scale > 1.5f * baseSize) {
        baseSize = 5.0f * baseSize;
    } else if (PhysicsObject::scale < baseSize / 6.0f) {
        baseSize = baseSize / 5.0f;
    }

    vertices = originalVertices;

    addNoise();
    calculateNormals();
    initBuffers();
}