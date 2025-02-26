#include "Shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <cstring>
#include <string_view>

std::string Shader::rootPath;

std::vector< CompilationErrorDetails> Shader::CompilationErrors;

std::map<std::string, unsigned int> Shader::List;

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

std::string CheckShaderCompileErrors(const GLuint shader)
{
    GLint hasCompiled = GL_FALSE;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

    if (hasCompiled != GL_TRUE)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        if (infoLog[0] != '\0') // Ensure error message exists
        {
            std::cerr << "SHADER_COMPILATION_ERROR for: " << "\n" << infoLog << std::endl;

            auto str = std::string(infoLog);
            return str;
        }
    }

    return std::string();
}

// Checks if the different Shaders have compiled properly
std::string CheckProgramLinkingErrors(const GLuint program)
{
    GLint hasCompiled = GL_FALSE;
    char infoLog[1024];

    glGetProgramiv(program, GL_LINK_STATUS, &hasCompiled);
    if (hasCompiled != GL_TRUE)
    {
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        if (infoLog[0] != '\0') // Ensure error message exists
        {
            std::cerr << "SHADER_LINKING_ERROR for: " << "\n" << infoLog << std::endl;

            auto str = std::string(infoLog);
            return str;
        }
    }

    return std::string();
}

void printErrorDetails(const std::vector<CompilationErrorDetails>& errorDetailsList) {
    for (const auto& details : errorDetailsList) {
        std::cout << "Line Number: " << details.lineNumber << '\n';
        std::cout << "Error Code: " << details.errorCode << '\n';
        std::cout << "Error Message: " << details.errorMessage << '\n';
        std::cout << "-------------------------\n";
    }
}

unsigned int Shader::CreateProgram(const std::string& programName, const char* vertexFile, const char* fragmentFile)
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
    /*auto vsStr = CheckShaderCompileErrors(vS);
    if (!vsStr.empty())
    {
        parseErrorMessage(vsStr.c_str());
    }*/

    unsigned int fS;
    fS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fS, 1, &fragmentSource, NULL);
    glCompileShader(fS);
    /*auto fsStr = CheckShaderCompileErrors(fS);
    if (!fsStr.empty())
    {
        parseErrorMessage(fsStr.c_str());
    }*/

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vS);
    glAttachShader(shaderProgram, fS);
    glLinkProgram(shaderProgram);
    auto prog = CheckProgramLinkingErrors(shaderProgram);
    if (!prog.empty())
    {
        ParseErrorMessage(prog.c_str());
    }

    glDeleteShader(vS);
    glDeleteShader(fS);

    //printErrorDetails(Shader::ShaderErrors);

    return shaderProgram;
}

unsigned int Shader::CreateProgramFromString(const std::string& programName, const std::string& vertexShaderData, const std::string& fragmentShaderData)
{
    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexShaderData.c_str();
    const char* fragmentSource = fragmentShaderData.c_str();

    unsigned int vS;
    vS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vS, 1, &vertexSource, nullptr);
    glCompileShader(vS);
    /*auto vsStr = CheckShaderCompileErrors(vS);
    if (!vsStr.empty())
    {
        parseErrorMessage(vsStr.c_str());
    }*/

    unsigned int fS;
    fS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fS, 1, &fragmentSource, NULL);
    glCompileShader(fS);
    /*auto fsStr = CheckShaderCompileErrors(fS);
    if (!fsStr.empty())
    {
        parseErrorMessage(fsStr.c_str());
    }*/

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vS);
    glAttachShader(shaderProgram, fS);
    glLinkProgram(shaderProgram);
    auto prog = CheckProgramLinkingErrors(shaderProgram);
    if (!prog.empty())
    {
        ParseErrorMessage(prog.c_str());
    }

    glDeleteShader(vS);
    glDeleteShader(fS);

    return shaderProgram;
}

std::vector<std::string> splitLines(const char* input)
{
    std::vector<std::string> lines;
    if (!input) return lines;

    const char* start = input;
    const char* newlinePos = nullptr;

    // Loop through the input and split by newline
    while ((newlinePos = strchr(start, '\n')) != nullptr) {
        // Create a substring from start to newline position (exclusive)
        lines.emplace_back(start, newlinePos);

        // Move the start position past the newline
        start = newlinePos + 1;
    }

    // Add the last part (after the final newline or the whole string if no newline)
    if (*start != '\0') {
        lines.emplace_back(start);
    }

    return lines;
}

void Shader::ParseErrorMessage(const char* log)
{
    std::vector<std::string> lines = splitLines(log);

    for (const auto& line : lines) {
        CompilationErrorDetails details;

        // Extract line number (between '(' and ')')
        size_t openParen = line.find('(');
        size_t closeParen = line.find(')', openParen);
        if (openParen != std::string::npos && closeParen != std::string::npos)
        {
            details.lineNumber = std::stoul(line.substr(openParen + 1, closeParen - openParen - 1));
        }
        else
        {
            details.lineNumber = -1;
        }

        // Extract error code (after "error ")
        size_t errorPos = line.find("error");
        if (errorPos != std::string::npos)
        {
            size_t colonPos = line.find(':', errorPos);
            if (colonPos != std::string::npos)
            {
                details.errorCode = line.substr(errorPos + 6, colonPos - (errorPos + 6));
                details.errorMessage = line.substr(colonPos + 2);
            }
        }

        // Add details to the list
        if (details.lineNumber != 0)
            Shader::CompilationErrors.push_back(details);
    }
}

