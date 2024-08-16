#pragma once

#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#define print(x)\
do\
{\
std::cout << x << '\n';\
}while(0)

class Mesh
{
};

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
        print("success");
    }

    auto meshes = scene->mMeshes;
    auto numMeshes = scene->mNumMeshes;

    /*for (unsigned int i = 0; i < numMeshes; i++)
    {
        
    }*/


    // everything will be deleted by the deconstructor automiclly
    return true;
}
