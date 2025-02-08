#include "Shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string Shader::rootPath;

const std::string get_file_contents(const std::string filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents); 
    }
    throw(errno);
}

// Checks if the different Shaders have compiled properly
void CheckCompileErrors(const uint32_t shader, const char* type)
{
    // Stores status of compilation
    GLint hasCompiled;
    // Character array to store error message in
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
}

unsigned int Shader::CreateProgram(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexPath = Shader::rootPath + vertexFile;
    std::string fragmentPath = Shader::rootPath + fragmentFile;

    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = get_file_contents(vertexPath.c_str());
    std::string fragmentCode = get_file_contents(fragmentPath.c_str());

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vS;
    vS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vS, 1, &vertexSource, nullptr);
    glCompileShader(vS);
    CheckCompileErrors(vS, "VERTEX");

    unsigned int fS;
    fS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fS, 1, &fragmentSource, NULL);
    glCompileShader(fS);
    CheckCompileErrors(vS, "FRAGMENT");

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vS);
    glAttachShader(shaderProgram, fS);
    glLinkProgram(shaderProgram);
    CheckCompileErrors(vS, "PROGRAM");

    glDeleteShader(vS);
    glDeleteShader(fS);

    return shaderProgram;
}
