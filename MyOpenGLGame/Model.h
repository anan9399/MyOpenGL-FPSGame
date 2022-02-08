#pragma once
#include"Shader.h"
#include"Mesh.h"
#include<vector>
#include<iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<map>


class Model
{
public:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<MeshTexture> textures_loaded;

    Model(std::string const path)
    {
        LoadModel(path);
    }
    void Draw(Shader* shader);

private:
    


    void LoadModel(std::string path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

