#include "Mesh.h"

StaticMesh::StaticMesh(VertexData& data, VertexFormat& format)
{
	glGenVertexArrays(1, &this->renderVao);

	glBindVertexArray(this->renderVao);

	for (unsigned int i = 0; i < format.attributes.size(); i++)
	{
		glGenBuffers(1, &this->vbos[i]);

		glBindBuffer(GL_ARRAY_BUFFER, this->vbos[i]);
		std::vector<float> dat = data.data.find(format.attributes[i].name)->second;
		glBufferData(GL_ARRAY_BUFFER, dat.size() * sizeof(float), dat.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(
			format.attributes[i].layoutIndex,
			format.attributes[i].numElements,
			format.attributes[i].type,
			false,
			format.attributes[i].stride,
			format.attributes[i].pointer
		);

		glGenBuffers(1, &this->indexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data.indices), data.indices.data(), GL_STATIC_DRAW);

		glBindVertexArray(this->positionVao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]); // as far as index 0 is for position.

		glBindVertexArray(0);
	}
}