#pragma once

#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>
#include "utils.h"
#include "texture.h"
#include "VAO.h"

class Mesh
{
public:
    std::vector<float> vertices{};
    std::vector<unsigned int> indices{};

    std::vector<unsigned int>attribs{3,3,2};

    std::vector<Texture> textures{};

    GLuint vao;
    GLuint ebo;
    GLuint vbo;

    void loadData()
    {
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);
        glCreateBuffers(1, &ebo);

        // 为 VBO 分配并填充数据
        glNamedBufferData(vbo, sizeof(float)*vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

        // 为 EBO 分配并填充数据
        glNamedBufferData(ebo, sizeof(GLuint)*indices.size(), &indices[0], GL_DYNAMIC_DRAW);

        unsigned int stride = 0;
        for(auto u : attribs)
        {
            stride += u;
        }
        unsigned int offsite = 0;
        for(size_t i = 0;i < attribs.size();i++)
        {
            glVertexArrayVertexBuffer(vao, i, vbo, offsite * sizeof(GLfloat), stride * sizeof(GLfloat));
            glVertexArrayAttribFormat(vao, i, attribs[i], GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vao, i, i);
            glEnableVertexArrayAttrib(vao, i);
    
            offsite += attribs[i];
        }
        
        // 绑定 EBO 到 VAO
        glVertexArrayElementBuffer(vao, ebo);
    }

    void draw()
    {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
};

struct Model
{
    std::vector<Mesh> meshes;

    void loadIn(const char * pFile)
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
            //print(importer.GetErrorString());
        }
        else
        {
            //print("success_mesh");
        }

        utils::printt("There is {} meshes in the model.",scene->mNumMeshes);

        auto meshes = scene->mMeshes;
        auto numMeshes = scene->mNumMeshes;

        /*print(numMeshes);
        print(meshes[0]->mNumVertices);*/

        for (unsigned int i = 0; i < numMeshes; i++)
        {
            this->meshes.push_back(Mesh());
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
                    this->meshes[i].vertices.push_back(m_positions[j][k]);
                }
                for(unsigned int k = 0; k < 3;k++)
                {
                    //per number
                    this->meshes[i].vertices.push_back(m_normals[j][k]);
                }
                for(unsigned int k = 0; k < 2;k++)
                {
                    //per number
                    this->meshes[i].vertices.push_back(m_uvs[j][k]);
                }
            }

            auto m_faces = meshes[i]->mFaces;

            for(unsigned int j = 0;j<meshes[i]->mNumFaces;j++)
            {
                //per face
                for(unsigned int k = 0;k<m_faces[j].mNumIndices;k++)
                {
                    //per num
                    this->meshes[i].indices.push_back(m_faces[j].mIndices[k]);
                }
            }
            this->meshes[i].loadData();
        }
    }
};

