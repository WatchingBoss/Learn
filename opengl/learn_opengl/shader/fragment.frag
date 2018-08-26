#version 330 core

out vec4 color;

in vec3 vertColor;
in vec2 TexCoor;

uniform sampler2D ourTexture;

void main()
{
//	color = vec4(vertColor, 1.0f);
	color = texture(ourTexture, TexCoor) * vec4(vertColor, 1.0f);
}
