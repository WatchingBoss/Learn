#shader vertex
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(0.2f, 0.7f, 0.5f, 1.0f);
}
