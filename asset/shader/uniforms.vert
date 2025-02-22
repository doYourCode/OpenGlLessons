#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;

uniform float timer;

float movementScale = 0.1f;

void main()
{
    color = aCol;
    texCoord = aTexCoord;

    gl_Position = vec4(
    aPos.x + sin(timer + gl_VertexID) * movementScale,
    aPos.y + cos(timer + gl_VertexID) * movementScale,
    0.0f,
    1.0f
    );
}