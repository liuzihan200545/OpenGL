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

