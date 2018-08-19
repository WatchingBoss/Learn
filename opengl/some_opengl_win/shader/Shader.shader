#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoor;

out vec2 v_texCoor;

void main()
{
    gl_Position = position;
	v_texCoor = texCoor;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoor;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoor);
    color = texColor;
};
