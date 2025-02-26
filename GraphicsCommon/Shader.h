#pragma once

#include<string>
#include <vector>
#include <map>
#include <glad/glad.h>

struct CompilationErrorDetails
{
	unsigned int lineNumber = 0;
	std::string errorCode;
	std::string errorMessage;
};

class Shader
{
public:

	static unsigned int CreateProgram(const std::string& programName, const char* vertexFile, const char* fragmentFile);

	static unsigned int CreateProgramFromString(const std::string& programName, const std::string& vertexShaderData, const std::string& fragmentShaderData);

	static void SetRootPath(const std::string& path) { Shader::rootPath = path; }

	static const std::vector< CompilationErrorDetails>& GetShaderErrors() { return Shader::CompilationErrors; }

	static void ResetShaderErrors() { Shader::CompilationErrors.clear(); }

private:

	static std::string rootPath;

	static std::vector< CompilationErrorDetails> CompilationErrors;

	static std::map<std::string, unsigned int> List;

	unsigned int CompileShader(GLenum shaderType, const std::string& shaderCode);

	static void ParseErrorMessage(const char* log);
};


