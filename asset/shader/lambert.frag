#version 460 core

in vec3 color;
in vec2 texCoord;
in vec3 normals;
in vec3 fragPos;

out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 cameraDirection;

void main()
{
    // Normalize the normal vector
    vec3 norm = normalize(normals);

    vec3 lightDir = normalize(lightDirection);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 finalColor = clamp(lightColor * (diff + ambientColor), 0.0, 1.0);

    FragColor = vec4(finalColor, 1.0);
} 