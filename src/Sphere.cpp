//
// Created by zowlyfon on 21/11/2020.
//

#include "Sphere.h"

Sphere::Sphere(float sectorCount, float stackCount, unsigned int subs) :
sectorCount(sectorCount), stackCount(stackCount), prevTime(glfwGetTime()),
subs(subs)
{

}

Sphere::~Sphere()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    indices.clear();
    vertices.clear();
}

void Sphere::init()
{
    //createSphere();


    createIcosahedron();

    rOffset = glm::vec3(Utility::randF() * 100.0f,
                        Utility::randF() * 100.0f,
                        Utility::randF() * 100.0f);

    for (int i = 0; i < subs; i++) {
        subdivideIcosahedron();
    }

    originalSphere = vertices;

    addNoise();


    //glGetNamedBufferSubData(vertexSSBO, 0, vertices.size() * sizeof(glm::vec3), vertices.data());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferStorage(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4) + normals.size() * sizeof(glm::vec3), nullptr, GL_DYNAMIC_STORAGE_BIT);

    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &vertices.front(), GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), &vertices.front());
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), normals.size() * sizeof(glm::vec3), &normals.front());

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);

    /*
    glGenBuffers(1, &NBO);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
    */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(vertices.size() * sizeof(glm::vec4)));
    glEnableVertexAttribArray(1);


    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
    //glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    rotAxis = glm::vec3(Utility::randF(),
                        Utility::randF(),
                        Utility::randF());

    rotStep = Utility::randF() * 30;
}

void Sphere::physics()
{
    auto time = glfwGetTime();
    GLdouble deltaT = time - prevTime;

    position += velocity * (GLfloat)deltaT;

    prevTime = time;
}

void Sphere::draw(Shader *shader, float playerSize)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position / playerSize);
    model = glm::scale(model, glm::vec3(scale / playerSize));
    model = glm::rotate(model, glm::radians(rotStep * (GLfloat)glfwGetTime()), rotAxis);

    //rOffset += (sinf(glfwGetTime()) + cosf(glfwGetTime())) / 100.0f;

    glUniformMatrix4fv(glGetUniformLocation(shader->getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "modelColor"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "rOffset"), 1, glm::value_ptr(rOffset));
    glUniform1f(glGetUniformLocation(shader->getShaderProgram(), "objScale"), scale);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Sphere::createSphere()
{
    vertices.clear();
    indices.clear();

    const float radius = 1.0f;
    auto pi = glm::pi<float>();

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float sectorStep = 2 * pi / sectorCount;
    float stackStep = pi / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = pi / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            vertices.push_back(glm::vec4(x, y, z, 1.0f));

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            //vertices.push_back(glm::vec4(nx, ny, nz, 1.0f));
        }
    }

    int k1, k2;

    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

}

void Sphere::createIcosahedron()
{
    const float t = (1.0f + glm::sqrt(5.0f)) / 2.0f;

    vertices.clear();

    vertices.push_back(glm::vec4(-1.0f, t, 0.0f, 1.0f));
    vertices.push_back(glm::vec4(1.0f, t, 0.0f, 1.0f));
    vertices.push_back(glm::vec4(-1.0f, -t, 0.0f, 1.0f));
    vertices.push_back(glm::vec4(1.0f, -t, 0.0f, 1.0f));

    vertices.push_back(glm::vec4(0.0f, -1.0f, t, 1.0f));
    vertices.push_back(glm::vec4(0.0f, 1.0f, t, 1.0f));
    vertices.push_back(glm::vec4(0.0f, -1.0f, -t, 1.0f));
    vertices.push_back(glm::vec4(0.0f, 1.0f, -t, 1.0f));

    vertices.push_back(glm::vec4(t, 0.0f, -1.0f, 1.0f));
    vertices.push_back(glm::vec4(t, 0.0f, 1.0f, 1.0f));
    vertices.push_back(glm::vec4(-t, 0.0f, -1.0f, 1.0f));
    vertices.push_back(glm::vec4(-t, 0.0f, 1.0f, 1.0f));

    for (auto &vertex : vertices) {
        vertex = glm::vec4(glm::normalize(glm::vec3(vertex)), 1.0f);
    }


    indices.push_back(0);
    indices.push_back(11);
    indices.push_back(5);

    indices.push_back(0);
    indices.push_back(5);
    indices.push_back(1);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(7);

    indices.push_back(0);
    indices.push_back(7);
    indices.push_back(10);

    indices.push_back(0);
    indices.push_back(10);
    indices.push_back(11);


    indices.push_back(1);
    indices.push_back(5);
    indices.push_back(9);

    indices.push_back(5);
    indices.push_back(11);
    indices.push_back(4);

    indices.push_back(11);
    indices.push_back(10);
    indices.push_back(2);

    indices.push_back(10);
    indices.push_back(7);
    indices.push_back(6);

    indices.push_back(7);
    indices.push_back(1);
    indices.push_back(8);


    indices.push_back(3);
    indices.push_back(9);
    indices.push_back(4);

    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(2);

    indices.push_back(3);
    indices.push_back(2);
    indices.push_back(6);

    indices.push_back(3);
    indices.push_back(6);
    indices.push_back(8);

    indices.push_back(3);
    indices.push_back(8);
    indices.push_back(9);


    indices.push_back(4);
    indices.push_back(9);
    indices.push_back(5);

    indices.push_back(2);
    indices.push_back(4);
    indices.push_back(11);

    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(10);

    indices.push_back(8);
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(9);
    indices.push_back(8);
    indices.push_back(1);
}

void Sphere::subdivideIcosahedron()
{
    verticesMap.clear();
    //std::vector<glm::vec4> tmpVertices;
    std::vector<GLuint> tmpIndices;

    //tmpVertices.swap(vertices);
    //tmpIndices.swap(indices);

    for (int i = 0; i < indices.size(); i += 3) {
        GLuint Ai = indices[i];
        GLuint Bi = indices[i + 1];
        GLuint Ci = indices[i + 2];

        GLuint ABi = getMidpoint(Ai, Bi);
        GLuint BCi = getMidpoint(Bi, Ci);
        GLuint CAi = getMidpoint(Ci, Ai);

        /* Triangle 1 = A, AB, CA */
        /* Triangle 2 = AB, B, BC */
        /* Triangle 3 = CA, BC, C */
        /* Triangle 4 = AB, BC, CA */

        tmpIndices.push_back(Ai);
        tmpIndices.push_back(ABi);
        tmpIndices.push_back(CAi);

        tmpIndices.push_back(ABi);
        tmpIndices.push_back(Bi);
        tmpIndices.push_back(BCi);

        tmpIndices.push_back(CAi);
        tmpIndices.push_back(BCi);
        tmpIndices.push_back(Ci);

        tmpIndices.push_back(ABi);
        tmpIndices.push_back(BCi);
        tmpIndices.push_back(CAi);
    }

    indices.swap(tmpIndices);
}

GLuint Sphere::getMidpoint(GLuint A, GLuint B)
{
    auto vertexExists = verticesMap.find(std::make_pair(A, B));
    if (vertexExists != verticesMap.end()) {
        return vertexExists->second;
    }

    vertexExists = verticesMap.find(std::make_pair(B, A));
    if (vertexExists != verticesMap.end()) {
        return vertexExists->second;
    }

    glm::vec3 Av = vertices[A];
    glm::vec3 Bv = vertices[B];

    glm::vec3 midPoint = (Av + Bv) / 2.0f;

    midPoint = glm::normalize(midPoint);

    auto pos = vertices.size();
    vertices.push_back(glm::vec4(midPoint, 1.0f));
    verticesMap.insert(std::make_pair(std::make_pair(A, B), pos));

    return pos;
}

/* Add noise with compute shader */
void Sphere::addNoise()
{
    ComputeShader computeShader("addSimplexNoise.comp.glsl");


    glUseProgram(computeShader.getShaderProgram());

    GLuint vertexSSBO;
    glGenBuffers(1, &vertexSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertexSSBO);
    //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertexSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_DYNAMIC_COPY);
    glUniform3fv(glGetUniformLocation(computeShader.getShaderProgram(), "offset"), 1, glm::value_ptr(rOffset));
    glUniform1f(glGetUniformLocation(computeShader.getShaderProgram(), "objScale"), scale);
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
    calculateNormals();
}

void Sphere::calculateNormals()
{
    normals.clear();
    normals.resize(vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
        normals[i] = glm::vec3(0.0f);
    }



    for (int i = 0; i < indices.size(); i += 3) {
        glm::vec3 A = glm::vec3(vertices[indices[i]]);
        glm::vec3 B = glm::vec3(vertices[indices[i + 1]]);
        glm::vec3 C = glm::vec3(vertices[indices[i + 2]]);

        glm::vec3 *An = &normals[indices[i]];
        glm::vec3 *Bn = &normals[indices[i + 1]];
        glm::vec3 *Cn = &normals[indices[i + 2]];

        glm::vec3 p = glm::cross(B - A, C - A);

        *An += p;
        *Bn += p;
        *Cn += p;
    }


    for (int i = 0; i < normals.size(); i++) {
        normals[i] = glm::normalize(normals[i]);
    }
}

void Sphere::updateMass()
{
    //createSphere();

    if (scale > 1.5f * baseSize) {
        baseSize = 5.0f * baseSize;
    } else if (scale < baseSize / 6.0f) {
        baseSize = baseSize / 5.0f;
    }

    vertices = originalSphere;
    addNoise();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferStorage(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4) + normals.size() * sizeof(glm::vec3), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), &vertices.front());
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), normals.size() * sizeof(glm::vec3), &normals.front());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
