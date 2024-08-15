#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexcoord;


uniform mat4 model;
uniform mat4 camMatrix;
uniform float scale;

out vec3 color;
out vec2 uv;

void main(){
	gl_Position = camMatrix * model * vec4(aPos,1.0f);
    color = aColor;
    uv = aTexcoord;
}