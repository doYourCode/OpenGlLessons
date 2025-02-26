#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>

struct VertexAttribute
{
	VertexAttribute(
		const std::string& name,
		GLenum type,
		unsigned int layoutIndex,
		unsigned int numElements,
		unsigned int stride,
		const void* pointer) : 
			name(name),
			type(type),
			layoutIndex(layoutIndex),
			numElements(numElements),
			stride(stride),
			pointer(pointer) { }

	std::string name = std::string();

	GLenum type = GL_FLOAT;

	unsigned int layoutIndex = 0;
	unsigned int numElements = 0;
	unsigned int stride = 0;

	const void* pointer = nullptr;
};

struct MeshFormat
{
	MeshFormat(const std::vector<VertexAttribute>& attributes) : attributes(attributes) {}

	std::vector<VertexAttribute> attributes = std::vector<VertexAttribute>();

	void addAttribute(const VertexAttribute& attrib)
	{
		attributes.push_back(attrib);
	}
};

namespace MeshFormats
{
	static const MeshFormat Pos2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr}
		});

	static const MeshFormat Pos3 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr}
		});

	static const MeshFormat Pos2Col3 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"color", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr}
		});

	static const MeshFormat Pos3Col3 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr}
		});

	static const MeshFormat Pos2Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr}
		});

	static const MeshFormat Pos3Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr}
		});

	static const MeshFormat Pos3Col3Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr}
		});

	static const MeshFormat Pos3Norm3Binorm3Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"binormal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
		});

	static const MeshFormat Pos3Norm3Binorm3_2_Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"binormal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"texCoord2", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
		});

	static const MeshFormat Pos3Col3Norm3Binorm3Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"binormal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
		});

	static const MeshFormat Pos3Col3Norm3Binorm3_2_Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"binormal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"texCoord2", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
		});

	static const MeshFormat Pos3Col4Norm3Binorm3Texcoord2 = MeshFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color", GL_FLOAT, 0, 4, sizeof(float) * 4, nullptr},
			{"normal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"binormal", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
		});
}

struct MeshData
{
	std::map<std::string, std::vector<float>> data = std::map<std::string, std::vector<float>>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();
};

struct RenderMesh
{
	RenderMesh(MeshData& data, MeshFormat& format);

	unsigned int renderVao = 0;
	unsigned int shadowVao = 0; // Position only.
	unsigned int indexSize = 0;
	unsigned int indexBuffer = 0;

	std::vector<unsigned int> vbos = std::vector<unsigned int>();
};

class SceneRenderer
{
public:



private:

	unsigned int currentVao;
	unsigned int currentShader;

};

