//
// Created by zowlyfon on 21/11/2020.
//

#include "Shader.h"

Shader::Shader(std::string vShaderName, std::string fShaderName)
{
    loadFile(&vShaderName, &vShaderSource);
    loadFile(&fShaderName, &fShaderSource);
    //loadFile(&gShaderName, &gShaderSource);

    initShader(&vShader, &vShaderSource, GL_VERTEX_SHADER);
    initShader(&fShader, &fShaderSource, GL_FRAGMENT_SHADER);
    //initShader(&gShader, &gShaderSource, GL_GEOMETRY_SHADER);

    linkShader();

    glDeleteShader(vShader);
    glDeleteShader(fShader);
    //glDeleteShader(gShader);
}

Shader::~Shader()
{

}

GLuint Shader::getShaderProgram()
{
    if (shaderProgram) {
        return shaderProgram;
    }
    return 0;
}

void Shader::initShader(GLuint *shader, std::string *shaderSource, GLenum shaderType)
{
    *shader = glCreateShader(shaderType);
    const char *shaderSourcePointer = shaderSource->c_str();
    glShaderSource(*shader, 1, &shaderSourcePointer, NULL);
    glCompileShader(*shader);

    int success;
    char infoLog[1024];
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(*shader, 1024, NULL, infoLog);
    }
}

void Shader::linkShader()
{
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    //glAttachShader(shaderProgram, gShader);

    glLinkProgram(shaderProgram);

    int success = 0;
    char infoLog[1024];
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, infoLog);
    }
}

int Shader::loadFile(std::string *fileName, std::string *data)
{
    std::ifstream file;
    std::string line;
    file.exceptions(std::ifstream::badbit);

    try {
        file.open(*fileName);
        while (std::getline(file, line)) {
            data->append(line.append("\n"));
            std::cout << line;
        }
        file.close();
    } catch (std::ifstream::failure &e) {
        std::cout << "Error: Shader file could not be read:\n" << *fileName << std::endl;
        return -1;
    }

    return 0;
}