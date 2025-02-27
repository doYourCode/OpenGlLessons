#pragma once

#include "VertexFormat.h"
#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>

#include <assimp/mesh.h>

struct VertexData
{
	std::map<std::string, std::vector<float>> data = std::map<std::string, std::vector<float>>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();

	static void CreateFromAssimpMesh(VertexData& meshDataInstance, aiMesh* assimpMesh); // change it later
};

struct StaticMesh
{
	StaticMesh(VertexData& data, VertexFormat& format);

	unsigned int renderVao = 0;
	unsigned int positionVao = 0; // Useful for depth/shadow techniques.
	unsigned int indexSize = 0;
	unsigned int indexBuffer = 0;

	std::vector<unsigned int> vbos = std::vector<unsigned int>();
};

