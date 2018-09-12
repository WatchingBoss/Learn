#version 330 core

out vec4 color;

in vec2 TexCoor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform vec3 u_color;

void main()
{
	color = mix(texture(ourTexture1, TexCoor), texture(ourTexture2, TexCoor), 0.25);
}
