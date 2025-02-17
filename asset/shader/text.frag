#version 460 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

// solution based on https://drewcassidy.me/2020/06/26/sdf-antialiasing/

void main()
{
    float dist = 0.5 - texture(text, TexCoords).r;

    vec2 ddist = vec2(dFdx(dist), dFdy(dist));

    float opacity = clamp(0.5 - (dist / length(ddist)), 0.0, 1.0);

    color = vec4(textColor, opacity);
}