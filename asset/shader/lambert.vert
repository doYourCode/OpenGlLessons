#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormals;

out vec3 color;
out vec2 texCoord;
out vec3 normals;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    color = aCol;
    texCoord = aTexCoord;

    fragPos = vec3(transform * vec4(aPos, 1.0));

    normals = normalize(mat3(transpose(inverse(transform))) * aNormals);

    gl_Position = vec4(fragPos, 1.0f) * projection * view;
}