#pragma once

#include<string>

class Shader
{
public:
	static unsigned int CreateProgram(const char* vertexFile, const char* fragmentFile);

	static void SetRootPath(const std::string path) { Shader::rootPath = path; }

private:
	static std::string rootPath;
};

