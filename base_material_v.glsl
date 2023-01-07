#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in float color;
// layout (location = 2) in vec2 uv_in;
out vec3 vertex_color;
// out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vertex_color = vec3(color);
    // uv = uv_in;
}

