#version 330 core

out vec4 Fragcolor;

in vec3 color;
in vec2 uv;
uniform sampler2D t0;

void main(){
    Fragcolor = vec4(texture(t0,uv).xyz,1.0f);
}