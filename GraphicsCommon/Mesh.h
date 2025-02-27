#pragma once

#include "Vertex.h"
#include <vector>


struct StaticMesh
{
	StaticMesh(VertexData& data, VertexFormat& format);

	unsigned int renderVao = 0;
	unsigned int positionVao = 0; // Useful for depth/shadow techniques.
	unsigned int indexSize = 0;
	unsigned int indexBuffer = 0;

	std::vector<unsigned int> vbos = std::vector<unsigned int>();
};

