//
// Created by zowlyfon on 21/11/2020.
//

#ifndef GAMEENGINE_SPHERE_H
#define GAMEENGINE_SPHERE_H

#include "PhysicsObject.h"
#include "ComputeShader.h"

#include <map>
#include <algorithm>
#include <execution>
#include <map>

class Sphere : public PhysicsObject{
public:
    Sphere(float sectorCount=256.0f, float stackCount=128.0f, unsigned int subs=4);
    ~Sphere();
    void init() override;
    void physics() override;
    void draw(Shader *shader, float playerSize) override;
    void updateMass() override;
    void calculateNormals() override;

private:
    void createSphere();
    void createIcosahedron();
    void subdivideIcosahedron();
    GLuint getMidpoint(GLuint A, GLuint B);
    void addNoise();

    std::map<std::pair<GLuint, GLuint>, GLuint> verticesMap;

    std::vector<glm::vec4> originalSphere;

    float sectorCount;
    float stackCount;
    GLdouble prevTime;
    glm::vec3 rOffset;
    glm::vec3 rotAxis;
    GLfloat rotStep;
    unsigned int subs;
};


#endif //GAMEENGINE_SPHERE_H
