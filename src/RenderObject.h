//
// Created by zowlyfon on 21/11/2020.
//

#ifndef GAMEENGINE_RENDEROBJECT_H
#define GAMEENGINE_RENDEROBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include <vector>
#include <cmath>
#include <algorithm>
#include <execution>

#include "Shader.h"
#include "Utility.h"
#include "ComputeShader.h"

class RenderObject {
public:
    RenderObject();
    ~RenderObject();
    virtual void init();
    virtual void draw(float playerSize);

    glm::vec3 position;
    glm::vec3 color;
    GLfloat scale;

    std::shared_ptr<Shader> shader;
    std::shared_ptr<ComputeShader> computeShader;

protected:
    virtual void initBuffers();
    virtual void calculateNormals();
    virtual void runComputeShader();

    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLuint> indices;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint NBO;
};


#endif //GAMEENGINE_RENDEROBJECT_H
