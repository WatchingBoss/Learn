#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;

out vec3 vertColor;

uniform vec3 newSize;

void main()
{
	gl_Position = vec4(position * newSize, 1.0);
	vertColor = aColor * (newSize + vec3(0.0, 0.0, 0.5) * aColor);
}

#shader fragment
#version 330 core

out vec4 color;
in vec3 vertColor;

void main()
{
	color = vec4(vertColor, 1.0f);
}
