#version 330 core

out vec4 color;

in vec3 vertColor;
in vec2 TexCoor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
//	color = vec4(vertColor, 1.0f);
	color = mix(texture(ourTexture1, TexCoor), texture(ourTexture2, TexCoor), 0.25);
}
