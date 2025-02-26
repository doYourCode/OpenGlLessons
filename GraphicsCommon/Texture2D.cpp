#include "Texture2D.h"

#include "stb_image.h"

#include<cerrno>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

void SetTexture(
	const unsigned char* data,
	unsigned int width,
	unsigned int height,
	unsigned int numberOfColorChannels);

unsigned int Texture2D::LoadFromFile(
	std::string const& filePath,
	GLint minFilter,
	GLint magFilter,
	GLint wrap,
	const glm::vec3& borderColor,
	bool invertVertical)
{
	// Carrega os dados do arquivo de imagem
	int width;
	int height;
	int numberOfColorChannels;

	stbi_set_flip_vertically_on_load(invertVertical);

	unsigned char* bytes = stbi_load(
		filePath.c_str(),
		&width,
		&height,
		&numberOfColorChannels,
		0);

	// Configura e aloca memória de vídeo para guardar a imagem,
	// atribuindo uma id para acessá-la.
	unsigned int textureId;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(borderColor));

	SetTexture(bytes, width, height, numberOfColorChannels);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}

void SetTexture(
	const unsigned char* data,
	unsigned int width,
	unsigned int height,
	unsigned int numberOfColorChannels)
{
	/*
	* A textura precisa ser alocada na vram de acordo com o numero 
	* de canais de cor, uma vez que há diferentes formatos de pixel 
	* para cada caso.
	*/
	if (numberOfColorChannels == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_SRGB_ALPHA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data
		);
	else if (numberOfColorChannels == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_SRGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data
		);
	else if (numberOfColorChannels == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_SRGB,
			width,
			height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			data
		);
	else
		throw std::invalid_argument("Texture type recognition failed");
}
