#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>
#include <assimp/mesh.h>

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
		pointer(pointer) {
	}

	std::string name;

	GLenum type = GL_FLOAT;

	unsigned int layoutIndex = 0;
	unsigned int numElements = 0;
	unsigned int stride = 0;

	const void* pointer = nullptr;
};

struct VertexFormat
{
	explicit VertexFormat(std::vector<VertexAttribute> attributes) : attributes(std::move(attributes)) {}

	std::vector<VertexAttribute> attributes;

	void addAttribute(const VertexAttribute& attrib)
	{
		attributes.push_back(attrib);
	}
};

struct VertexData
{
	std::map<std::string, std::vector<float>> data;
	std::vector<unsigned int> indices;

	static void CreateFromAssimpMesh(VertexData& meshDataInstance, aiMesh* assimpMesh);
};

namespace VertexFormats
{
	/// <summary>
	/// Position (x, y) only.
	/// - Better use for 2d rendering.
	/// </summary>
	inline const VertexFormat Pos2 = VertexFormat(
		{
			{"position", GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
		});

	/// <summary>
	/// Position (x, y, z) only.
	/// </summary>
	inline const VertexFormat Pos3 = VertexFormat(
		{
			{"position", GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
		});

	/// <summary>
	/// Position (x, y) and color (r, g, b).
	/// - Better use for 2d rendering.
	/// </summary>
	inline const VertexFormat Pos2Col3 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
		});

	/// <summary>
	/// Position (x, y, z) and color (r, g, b).
	/// </summary>
	inline const VertexFormat Pos3Col3 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
		});

	/// <summary>
	/// Position (x, y) and color (r, g, b, a).
	/// - Better use for 2d rendering.
	/// </summary>
	inline const VertexFormat Pos2Col4 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
		});

	/// <summary>
	/// Position (x, y, z) and color (r, g, b, a).
	/// </summary>
	inline const VertexFormat Pos3Col4 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
		});

	/// <summary>
	/// Position (x, y) and a single texCoord (u, v).
	/// </summary>
	inline const VertexFormat Pos2Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"texCoord1",	GL_FLOAT, 1, 2, sizeof(float) * 2, nullptr},
		});

	/// <summary>
	/// Position (x, y) and two texCoords (u, v).
	/// </summary>
	inline const VertexFormat Pos2_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 2, sizeof(float) * 2, nullptr},
			{"texCoord1",	GL_FLOAT, 1, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
		});

	/// <summary>
	/// Position (x, y, z) and a single texCoord (u, v).
	/// </summary>
	inline const VertexFormat Pos3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 1, 2, sizeof(float) * 2, nullptr},
		});

	/// <summary>
	/// Position (x, y, z) and two texCoords (u, v).
	/// </summary>
	inline const VertexFormat Pos3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 1, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"texCoord1",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"texCoord1",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Norm3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Norm3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 2, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Norm3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Norm3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Norm3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Norm3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Norm3Tan3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Norm3Tan3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 3, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Norm3Tan3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Norm3Tan3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 5, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Norm3Tan3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Norm3Tan3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 4, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 5, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Norm3Tan3Bitan3Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"bitangent",	GL_FLOAT, 4, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 5, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col3Norm3Tan3Bitan3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 3, sizeof(float) * 3, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"bitangent",	GL_FLOAT, 4, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 5, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 6, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Norm3Tan3BitanTexcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"bitangent",	GL_FLOAT, 4, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 5, 2, sizeof(float) * 2, nullptr},
		});

	inline const VertexFormat Pos3Col4Norm3Tan3Bitan3_2_Texcoord2 = VertexFormat(
		{
			{"position",	GL_FLOAT, 0, 3, sizeof(float) * 3, nullptr},
			{"color",		GL_FLOAT, 1, 4, sizeof(float) * 4, nullptr},
			{"normal",		GL_FLOAT, 2, 3, sizeof(float) * 3, nullptr},
			{"tangent",		GL_FLOAT, 3, 3, sizeof(float) * 3, nullptr},
			{"bitangent",	GL_FLOAT, 4, 3, sizeof(float) * 3, nullptr},
			{"texCoord1",	GL_FLOAT, 5, 2, sizeof(float) * 2, nullptr},
			{"texCoord2",	GL_FLOAT, 6, 2, sizeof(float) * 2, nullptr},
		});
}

