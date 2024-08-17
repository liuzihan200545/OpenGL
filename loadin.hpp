#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>
#include "utils.h"
#include "texture.h"
#include "VAO.h"

namespace md
{
    class Material
    {
    public:
        Texture diffuse_texture;
        Texture specular_texture;
    };

    struct Mesh
    {
        unsigned int size;
        unsigned int offsite;
        //Material mat;
    };

    class Model
    {
    public:
        std::vector<Mesh> meshes;

        std::vector<float> vertices;

        std::vector<unsigned int> indices;

        void loadin(const char * pFile);

        void draw()
        {
            glBindVertexArray(vao);
            for(auto& u:meshes)
            {
                glDrawElements(GL_TRIANGLES, u.size , GL_UNSIGNED_INT,(void*)(u.offsite*sizeof(unsigned int)));
            }
            glBindVertexArray(0);
        }

    private:

        GLuint vao;
        
        GLuint ebo;
        
        GLuint vbo;
    
    };

    inline void Model::loadin(const char* pFile)
    {
        Assimp::Importer importer;
    
        const aiScene* scene = importer.ReadFile(pFile,
                                                 aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);

        if (nullptr == scene)
        {
            utils::printt("Error in loading {}.",pFile);
        }

        utils::printt("There is {} meshes in the model.",scene->mNumMeshes);

        auto meshes = scene->mMeshes;
        auto numMeshes = scene->mNumMeshes;

        unsigned int offsite_indice = 0;
        unsigned int offsite_vertice = 0;

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
                    vertices.push_back(m_positions[j][k]);
                }
                for(unsigned int k = 0; k < 3;k++)
                {
                    //per number
                    vertices.push_back(m_normals[j][k]);
                }
                for(unsigned int k = 0; k < 2;k++)
                {
                    //per number
                    vertices.push_back(m_uvs[j][k]);
                }
            }

            auto m_faces = meshes[i]->mFaces;

            for(unsigned int j = 0;j<meshes[i]->mNumFaces;j++)
            {
                //per face
                for(unsigned int k = 0;k<m_faces[j].mNumIndices;k++)
                {
                    //per num
                    indices.push_back(m_faces[j].mIndices[k]+offsite_vertice);
                }
            }
            Mesh _mesh {meshes[i]->mNumFaces*3,offsite_indice};
            this->meshes.push_back(_mesh);
            offsite_indice += meshes[i]->mNumFaces*3;
            offsite_vertice += meshes[i]->mNumVertices;
        }
        
        // bind vao,vbo and ebo

        
        std::vector<unsigned int>attribs = {3,3,2};
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
}

