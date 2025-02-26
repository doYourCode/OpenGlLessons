#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include <stack>

class Mesh_PosColUvNormals
{
public:

    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;

    bool loadFromFile(const std::string& filename);

private:

    void processNode(aiNode* root, const aiScene* scene);

    void processMesh(const aiMesh& mesh, const aiScene* scene);
};