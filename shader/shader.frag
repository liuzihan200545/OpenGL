#version 330 core

out vec4 Fragcolor;

in vec4 color;

void main(){
    Fragcolor = color;
}