//
// Created by zowlyfon on 23/11/2020.
//

#include "ComputeShader.h"

ComputeShader::ComputeShader(std::string shaderName)
{
    loadFile(&shaderName, &shaderSource);

    initShader(&shader, &shaderSource, GL_COMPUTE_SHADER);

    linkShader();
}

ComputeShader::~ComputeShader()
{

}

GLuint ComputeShader::getShaderProgram()
{
    if (shaderProgram) {
        return shaderProgram;
    }
    return 0;
}

void ComputeShader::initShader(GLuint *shader, std::string *shaderSource, GLenum shaderType)
{
    *shader = glCreateShader(shaderType);
    const char *shaderSourcePointer = shaderSource->c_str();
    glShaderSource(*shader, 1, &shaderSourcePointer, NULL);
    glCompileShader(*shader);

    int success = 0;
    char infoLog[1024];
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(*shader, 1024, NULL, infoLog);
    }
}


void ComputeShader::linkShader()
{
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, shader);

    glLinkProgram(shaderProgram);

    int success = 0;
    char infoLog[1024];
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, infoLog);
    }
}

int ComputeShader::loadFile(std::string *fileName, std::string *data)
{
    std::ifstream file;
    std::string line;
    file.exceptions(std::ifstream::badbit);

    try {
        file.open(*fileName);
        while (std::getline(file, line)) {
            data->append(line.append("\n"));
            //std::cout << line;
        }
        file.close();
    } catch (std::ifstream::failure &e) {
        std::cout << "Error: Shader file could not be read:\n" << *fileName << std::endl;
        return -1;
    }

    return 0;
}