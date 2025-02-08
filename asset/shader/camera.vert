#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    color = aCol;
    texCoord = aTexCoord;

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f) * transform * projection * view;
}