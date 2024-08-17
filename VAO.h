#pragma once

#include <glad/glad.h>
#include <vector>

using namespace std;

class VAO
{
private:
    GLuint vao;
    GLuint ebo;
    GLuint vbo;

    size_t indices_size;

public:
    /*VAO(const vector<float>& vertices,const vector<unsigned int>& indices)
    {
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);
        glCreateBuffers(1, &ebo);

        // 为 VBO 分配并填充数据
        glNamedBufferData(vbo, sizeof(float)*vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

        // 为 EBO 分配并填充数据
        glNamedBufferData(ebo, sizeof(GLuint)*indices.size(), &indices[0], GL_DYNAMIC_DRAW);

        // 设置顶点属性指针
        // 位置属性
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, 8 * sizeof(GLfloat));
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 0, 0);
        glEnableVertexArrayAttrib(vao, 0);

        // 颜色属性
        glVertexArrayVertexBuffer(vao, 1, vbo, 3 * sizeof(GLfloat), 8 * sizeof(GLfloat));
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 1, 1);
        glEnableVertexArrayAttrib(vao, 1);

        glVertexArrayVertexBuffer(vao, 2, vbo, 6 * sizeof(GLfloat), 8 * sizeof(GLfloat));
        glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 2, 2);
        glEnableVertexArrayAttrib(vao, 2);

        // 绑定 EBO 到 VAO
        glVertexArrayElementBuffer(vao, ebo);

        indices_size = indices.size();
    }*/

    VAO(const vector<float>& vertices,const vector<unsigned int>& indices,vector<unsigned int> attribs)
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

        indices_size = indices.size();
    }

    VAO& operator=(const VAO& _vao)
    {
        this->vao = _vao.vao;
        this->ebo = _vao.ebo;
        this->vbo = _vao.vbo;
    }

    void draw() const 
    {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices_size , GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    ~VAO()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
    
};
