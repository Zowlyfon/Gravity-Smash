//
// Created by zowlyfon on 23/11/2020.
//

#ifndef GAMEENGINE_COMPUTESHADER_H
#define GAMEENGINE_COMPUTESHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>

class ComputeShader {
public:
    ComputeShader(std::string shaderName);
    ~ComputeShader();
    GLuint getShaderProgram();

private:
    int loadFile(std::string *fileName, std::string *data);
    void initShader(GLuint *shader, std::string *shaderSource, GLenum shaderType);
    void linkShader();

    std::string shaderSource;

    GLuint shader;

    GLuint shaderProgram;

    int x;
    int y;
    int z;
};


#endif //GAMEENGINE_COMPUTESHADER_H
