#version 450 core

in vec3 color;
in vec2 uv;

out vec4 FragColor;

uniform sampler2D t;

void main() {
    FragColor = vec4(texture(t,uv));
}