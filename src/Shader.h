//
// Created by zowlyfon on 21/11/2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <string>
#include <iostream>

class Shader {
public:
    Shader(std::string vShaderName, std::string fShaderName);
    ~Shader();

    GLuint getShaderProgram();

private:
    int loadFile(std::string *fileName, std::string *data);
    void initShader(GLuint *shader, std::string *shaderSource, GLenum shaderType);
    void linkShader();

    std::string vShaderSource;
    std::string fShaderSource;
    //std::string gShaderSource;

    GLuint vShader;
    GLuint fShader;
    //GLuint gShader;
    GLuint shaderProgram;
};

#endif //GAMEENGINE_SHADER_H
