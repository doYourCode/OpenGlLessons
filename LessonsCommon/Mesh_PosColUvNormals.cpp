#include "Mesh_PosColUvNormals.h"

#define UNUSED(x) (void)(x)

bool Mesh_PosColUvNormals::loadFromFile(const std::string& filename)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return false;
    }

    processNode(scene->mRootNode, scene);
    return true;
}

void Mesh_PosColUvNormals::processNode(aiNode* root, const aiScene* scene)
{
    std::stack<aiNode*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        aiNode const* node = nodeStack.top();
        nodeStack.pop();

        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh const* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(*mesh, scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            nodeStack.push(node->mChildren[i]);
        }
    }
}

void Mesh_PosColUvNormals::processMesh(const aiMesh& mesh, const aiScene* scene)
{
    UNUSED(scene);

    positions.reserve(positions.size() + mesh.mNumVertices * 3);
    normals.reserve(normals.size() + mesh.mNumVertices * 3);
    texCoords.reserve(texCoords.size() + mesh.mNumVertices * 2);
    indices.reserve(indices.size() + mesh.mNumFaces * 3);

    for (unsigned int i = 0; i < mesh.mNumVertices; i++)
    {
        positions.push_back(mesh.mVertices[i].x);
        positions.push_back(mesh.mVertices[i].y);
        positions.push_back(mesh.mVertices[i].z);

        normals.push_back(mesh.mNormals[i].x);
        normals.push_back(mesh.mNormals[i].y);
        normals.push_back(mesh.mNormals[i].z);

        if (mesh.mTextureCoords[0])
        {
            texCoords.push_back(mesh.mTextureCoords[0][i].x);
            texCoords.push_back(mesh.mTextureCoords[0][i].y);
        }
        else
        {
            texCoords.push_back(0.0f);
            texCoords.push_back(0.0f);
        }
    }

    for (unsigned int i = 0; i < mesh.mNumFaces; i++)
    {
        aiFace face = mesh.mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
}
