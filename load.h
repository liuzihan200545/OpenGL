#pragma once

#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>

#include "structs.h"
#include "utils.h"
#include "texture.h"
#include "VAO.h"

std::vector<float> vertices_load;
std::vector<unsigned int> indices_load;
std::vector<Texture> textures;

#define print(x)\
do\
{\
std::cout << x << '\n';\
}while(0)

bool loadMesh(const std::string& pFile)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);

    if (nullptr == scene)
    {
        print(importer.GetErrorString());
        return false;
    }
    else
    {
        print("success_mesh");
    }

    utils::printt("There is {} meshes in the model.",scene->mNumMeshes);

    auto meshes = scene->mMeshes;
    auto numMeshes = scene->mNumMeshes;

    /*print(numMeshes);
    print(meshes[0]->mNumVertices);*/

    for (unsigned int i = 0; i < numMeshes; i++)
    {
        // per mesh
        auto m_positions = meshes[i]->mVertices;
        auto m_normals = meshes[i]->mNormals;
        auto m_uvs = meshes[i]->mTextureCoords[0];
        
        for(unsigned int j = 0;j< meshes[i]->mNumVertices;j++)
        {
            //per vertice
            for(unsigned int k = 0; k < 3;k++)
            {
                //per number
                vertices_load.push_back(m_positions[j][k]);
            }
            for(unsigned int k = 0; k < 3;k++)
            {
                //per number
                vertices_load.push_back(m_normals[j][k]);
            }
            for(unsigned int k = 0; k < 2;k++)
            {
                //per number
                vertices_load.push_back(m_uvs[j][k]);
            }
        }

        auto m_faces = meshes[i]->mFaces;

        for(unsigned int j = 0;j<meshes[i]->mNumFaces;j++)
        {
            //per face
            for(unsigned int k = 0;k<m_faces[j].mNumIndices;k++)
            {
                //per num
                indices_load.push_back(m_faces[j].mIndices[k]);
            }
        }
    }
    // everything will be deleted by the deconstructor automiclly
    return true;
}

Texture load_texture(const char* pFile)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);

    if (nullptr == scene)
    {
        print(importer.GetErrorString());
    }
    else
    {
        print("success_texture");
    }

    auto meshes = scene->mMeshes;
    auto numMeshes = scene->mNumMeshes;

    for(int i = 0;i < numMeshes ; i++)
    {
        auto mesh = meshes[i];
        aiString str;
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        str = "";
        //material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        material->GetTexture(aiTextureType_DIFFUSE,0,&str);
        //��ͼ·��
        std::string dic = std::string(str.C_Str());
        auto texture = Texture(dic.c_str());
        texture.LoadTexture();
        return texture;   
    }
}

bool loadMesh(const std::string& pFile,Mesh& _m)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);

    if (nullptr == scene)
    {
        print(importer.GetErrorString());
        return false;
    }
    else
    {
        print("success_mesh");
    }

    utils::printt("There is {} meshes in the model.",scene->mNumMeshes);

    auto meshes = scene->mMeshes;
    auto numMeshes = scene->mNumMeshes;

    /*print(numMeshes);
    print(meshes[0]->mNumVertices);*/

    for (unsigned int i = 0; i < numMeshes; i++)
    {
        // per mesh
        auto m_positions = meshes[i]->mVertices;
        auto m_normals = meshes[i]->mNormals;
        auto m_uvs = meshes[i]->mTextureCoords[0];
        
        for(unsigned int j = 0;j< meshes[i]->mNumVertices;j++)
        {
            //per vertice
            for(unsigned int k = 0; k < 3;k++)
            {
                //per number
                _m.vertices.push_back(m_positions[j][k]);
            }
            for(unsigned int k = 0; k < 3;k++)
            {
                //per number
                _m.vertices.push_back(m_normals[j][k]);
            }
            for(unsigned int k = 0; k < 2;k++)
            {
                //per number
                _m.vertices.push_back(m_uvs[j][k]);
            }
        }

        auto m_faces = meshes[i]->mFaces;

        for(unsigned int j = 0;j<meshes[i]->mNumFaces;j++)
        {
            //per face
            for(unsigned int k = 0;k<m_faces[j].mNumIndices;k++)
            {
                //per num
                _m.indices.push_back(m_faces[j].mIndices[k]);
            }
        }
    }
    // everything will be deleted by the deconstructor automiclly
    return true;
}
