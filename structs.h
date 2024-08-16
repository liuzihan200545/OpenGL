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
private:
    VAO vao;

    std::vector<Texture> textures;
    
public:

    /*Mesh(const VAO& _vao,)
    {
        vao = _vao;
        
    }*/
    
    void Draw()
    {
        textures[0].Bind();
        vao.draw();
        textures[0].Unbind();
    }
    
};

