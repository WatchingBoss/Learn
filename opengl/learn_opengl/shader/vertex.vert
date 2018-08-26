#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoor;

out vec3 vertColor;
out vec2 TexCoor;

uniform vec3 newSize;

void main()
{
	gl_Position = vec4(position * newSize, 1.0);
	vertColor = aColor * newSize;
	TexCoor = aTexCoor;
}
