#include "Vertex.h"

#include <assimp/mesh.h>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

/*
* **1.6. Code Duplication
    Issue: The CreateFromAssimpMesh function has repetitive code for extracting positions, normals, and texture coordinates.
    This can be refactored to reduce duplication.
    Fix: Create a helper function to handle the extraction of vertex attributes.
*/
void VertexData::CreateFromAssimpMesh(VertexData& meshDataInstance, aiMesh* assimpMesh)
{
    if (!assimpMesh)
    {
        throw std::invalid_argument("Assimp mesh is null.");
    }

    // Extract vertex positions
    if (assimpMesh->HasPositions())
    {
        std::vector<float>& positions = meshDataInstance.data["position"];
        positions.reserve(assimpMesh->mNumVertices * 3);

        for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
        {
            const aiVector3D& v = assimpMesh->mVertices[i];
            positions.insert(positions.end(), { v.x, v.y, v.z });
        }
    }
    else
    {
        throw std::runtime_error("Mesh does not contain vertex positions.");
    }

    // Extract normals
    if (assimpMesh->HasNormals())
    {
        std::vector<float>& normals = meshDataInstance.data["normal"];
        normals.reserve(assimpMesh->mNumVertices * 3);

        for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
        {
            const aiVector3D& n = assimpMesh->mNormals[i];
            normals.insert(normals.end(), { n.x, n.y, n.z });
        }
    }

    // Extract texture coordinates (only the first UV channel for now)
    if (assimpMesh->HasTextureCoords(0))
    {
        std::vector<float>& texcoords = meshDataInstance.data["texCoord1"];
        texcoords.reserve(assimpMesh->mNumVertices * 2);

        for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
        {
            const aiVector3D& uv = assimpMesh->mTextureCoords[0][i];
            texcoords.insert(texcoords.end(), { uv.x, uv.y });
        }
    }

    if (assimpMesh->HasTangentsAndBitangents())
    {
        std::vector<float>& tangents = meshDataInstance.data["tangent"];
        std::vector<float>& bitangents = meshDataInstance.data["bitangent"];
        tangents.reserve(assimpMesh->mNumVertices * 3);
        bitangents.reserve(assimpMesh->mNumVertices * 3);
        for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i) {
            const aiVector3D& t = assimpMesh->mTangents[i];
            const aiVector3D& b = assimpMesh->mBitangents[i];
            tangents.insert(tangents.end(), { t.x, t.y, t.z });
            bitangents.insert(bitangents.end(), { b.x, b.y, b.z });
        }
    }

    // Extract indices
    meshDataInstance.indices.reserve(assimpMesh->mNumFaces * 3);
    for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i)
    {
        const aiFace& face = assimpMesh->mFaces[i];
        if (face.mNumIndices == 3) // Ensure it's a triangle
        {
            meshDataInstance.indices.insert(meshDataInstance.indices.end(), { face.mIndices[0], face.mIndices[1], face.mIndices[2] });
        }
    }
}
