#version 450 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;

uniform mat4 camera_info;

void main() {
    gl_Position = camera_info * model * vec4(aPos,1.0f);
}
