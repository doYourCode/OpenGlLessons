#version 460 core

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 tex2 = texture(texture2, texCoord);
    FragColor = mix(texture(texture1, texCoord), tex2, tex2.a) * vec4(color, 1.0);
} 