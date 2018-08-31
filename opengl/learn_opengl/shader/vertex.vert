#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoor;

out vec2 TexCoor;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	TexCoor = aTexCoor;
}
