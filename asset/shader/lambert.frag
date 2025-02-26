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
uniform bool showTexture;

void main()
{
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 finalColor = clamp(lightColor * (diff + ambientColor), 0.0, 1.0);

    // Evite usar if/else se possível (o que não foi feito aqui
    // em favor da clareza do exemplo. O mesmo efeito poderia ser
    // obtido conforme comentário ao final deste arquivo.
    if (showTexture)
    {
        FragColor = vec4(finalColor * texture(texture1,texCoord).rgb , 1.0);
    }
    else
    {
        FragColor = vec4(finalColor, 1.0);
    }
} 