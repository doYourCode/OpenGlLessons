#pragma once

#include <glad/glad.h>

#include <glm/ext/vector_float3.hpp>

#include <string>

class Texture2D
{
public:

	static unsigned int LoadFromFile(
		std::string const& filePath,
		GLint minFilter = GL_LINEAR,
		GLint magFilter = GL_LINEAR,
		GLint wrap = GL_REPEAT,
		const glm::vec3& boderColor = glm::vec3(0.0f),
		bool invertVertical = false);

	static unsigned int LoadFromFile(
		std::string const& filePath,
		GLint wrap,
		const glm::vec3& boderColor = glm::vec3(0.0f),
		bool invertVertical = false)
	{
		return Texture2D::LoadFromFile(
			filePath,
			GL_LINEAR,
			GL_LINEAR,
			wrap,
			boderColor,
			invertVertical);
	}

	static unsigned int LoadFromFile(
		std::string const& filePath,
		bool invertVertical)
	{
		return Texture2D::LoadFromFile(
			filePath,
			GL_LINEAR,
			GL_LINEAR,
			GL_REPEAT,
			glm::vec3(0.0f),
			invertVertical);
	}

	static void SetRootPath(std::string const& rootPath)
		{ Texture2D::m_rootPath = rootPath; }

private:

	static std::string m_rootPath;
};

