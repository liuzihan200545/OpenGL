#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;

out vec3 color;
out vec2 uv;

uniform mat4 camera_info;

void main() {
    gl_Position = camera_info * vec4(aPos,1.0f);
    color = aColor;
    uv = aUv;
}