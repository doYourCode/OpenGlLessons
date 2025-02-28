#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

StaticMesh::StaticMesh(VertexData& data, VertexFormat& format)
{
	this->indexSize = (unsigned int) data.indices.size();

	glGenVertexArrays(1, &this->renderVao);
	glBindVertexArray(this->renderVao);

	this->vbos.resize(format.attributes.size());

	for (unsigned int i = 0; i < format.attributes.size(); i++)
	{
		glGenBuffers(1, &this->vbos[i]);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbos[i]);

		std::vector<float> dat = data.data.find(format.attributes[i].name)->second;
		glBufferData(GL_ARRAY_BUFFER, dat.size() * sizeof(float), dat.data(), GL_STATIC_DRAW); printf("SIZE %i\n",dat.size() * sizeof(float));

		glVertexAttribPointer(
			format.attributes[i].layoutIndex,
			format.attributes[i].numElements,
			format.attributes[i].type,
			false,
			format.attributes[i].stride,
			format.attributes[i].pointer
		);
		glEnableVertexAttribArray(format.attributes[i].layoutIndex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glGenBuffers(1, &this->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.indices.size(), data.indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CheckVAOState(this->renderVao, "At the end of StaticMesh constructor.");
	
}

StaticMesh StaticMesh::LoadFromFile(const std::string& filePath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Error loading mesh: " << importer.GetErrorString() << std::endl;
		return StaticMesh();
	}

	if (scene->mNumMeshes == 0) {
		std::cerr << "Error: No meshes found in file." << std::endl;
		return StaticMesh();
	}

	aiMesh* mesh = scene->mMeshes[0];

	if (!mesh->HasPositions() || !mesh->HasNormals() || !mesh->HasTextureCoords(0)) {
		std::cerr << "Error: Mesh does not contain required attributes." << std::endl;
		return StaticMesh();
	}

	VertexData vertexData;

	VertexData::CreateFromAssimpMesh(vertexData, mesh);

	VertexFormat vertexFormat = VertexFormats::Pos3Norm3Texcoord2;

	auto staticMesh = StaticMesh(vertexData, vertexFormat);

	return staticMesh;
}

StaticMesh::~StaticMesh()
{
	if (renderVao) glDeleteVertexArrays(1, &renderVao);
	if (positionVao) glDeleteVertexArrays(1, &positionVao);
	if (indexBuffer) glDeleteBuffers(1, &indexBuffer);

	for (auto vbo : vbos)
	{
		glDeleteBuffers(1, &vbo);
	}
}

void CheckVAOState(GLuint vao)
{
	glBindVertexArray(vao);

	GLint maxAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);

	std::cout << "VAO " << vao << " " << maxAttributes << " maxAttributes" << std::endl;

	for (GLint i = 0; i < maxAttributes; ++i)
	{
		GLint enabled;
		glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
		if (enabled)
		{
			std::cout << "Attribute " << i << " is enabled." << std::endl;

			GLint bufferBinding;
			glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &bufferBinding);
			std::cout << "    Bound to buffer ID: " << bufferBinding << std::endl;
		}
		else
		{
			std::cout << "Attribute " << i << " is NOT enabled." << std::endl;
		}
	}

	glBindVertexArray(0);
}

void CheckVAOState(GLuint vao, const std::string& context)
{
	std::cout << "Checking VAO state at: " << context << std::endl;

	glBindVertexArray(vao);

	GLint maxAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);

	std::cout << "VAO " << vao << " has " << maxAttributes << " max attributes." << std::endl;

	for (GLint i = 0; i < maxAttributes; ++i)
	{
		GLint enabled;
		glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
		if (enabled)
		{
			std::cout << "Attribute " << i << " is enabled." << std::endl;

			GLint bufferBinding;
			glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &bufferBinding);
			std::cout << "    Bound to buffer ID: " << bufferBinding << std::endl;
		}
		else
		{
			std::cout << "Attribute " << i << " is NOT enabled." << std::endl;
		}
	}

	glBindVertexArray(0);
}