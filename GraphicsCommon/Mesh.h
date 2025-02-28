#pragma once

#include "Vertex.h"
#include <vector>
#include <iostream>

struct StaticMesh
{
	StaticMesh() = default;

	~StaticMesh();

	StaticMesh(VertexData& data, VertexFormat& format);

	//StaticMesh(StaticMesh&& other) noexcept;
	//StaticMesh& operator=(StaticMesh&& other) noexcept;

	static StaticMesh LoadFromFile(const std::string& filePath);

	unsigned int renderVao = 0;
	unsigned int positionVao = 0; // Useful for depth/shadow techniques.
	unsigned int indexSize = 0;
	unsigned int indexBuffer = 0;

	std::vector<unsigned int> vbos;
};

void CheckVAOState(GLuint vao);

void CheckVAOState(GLuint vao, const std::string& context);
