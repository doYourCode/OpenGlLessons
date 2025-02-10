#version 460 core

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, texCoord);
} 