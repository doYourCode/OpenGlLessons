#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include "stb_image.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>


struct Texture
{
	GLuint ID;

	const char* type;


	Texture(const char* image, const char* texType, GLuint slot);


	void TexUnit(unsigned int programId, const char* uniform, GLuint unit) const;

	void Bind() const;

	void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	void Delete() const { glDeleteTextures(1, &ID); }


	static void SetRootPath(std::string path) { Texture::rootPath = path; }

private:

	GLuint unit;

	static std::string rootPath;
};