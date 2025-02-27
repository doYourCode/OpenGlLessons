#include "Vertex.h"

#include <assimp/mesh.h>
#include <map>
#include <vector>
#include <string>

void VertexData::CreateFromAssimpMesh(VertexData& meshDataInstance, aiMesh* assimpMesh)
{
    if (!assimpMesh)
        return;

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
