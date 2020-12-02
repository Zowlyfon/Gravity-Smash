//
// Created by zowlyfon on 27/11/2020.
//

#include "IcoSphere.h"

IcoSphere::IcoSphere(unsigned int subs) : subs(subs)
{}

IcoSphere::~IcoSphere() {
    verticesMap.clear();
    originalVertices.clear();
};

void IcoSphere::init()
{
    initIcosphere();
}

void IcoSphere::initIcosphere()
{
    createIcosahedron();

    for (int i = 0; i < subs; i++) {
        subdivideMesh();
    }

    originalVertices = vertices;
}

void IcoSphere::draw(float playerSize)
{

}

void IcoSphere::createIcosahedron()
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

void IcoSphere::subdivideMesh()
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

GLuint IcoSphere::getMidpoint(GLuint A, GLuint B)
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