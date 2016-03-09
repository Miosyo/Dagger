#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 outColor;
out vec2 outUV;

void main()
{
	mat4 MVP = projection * view * model;
    gl_Position = MVP * vec4(position, 1.0);
	outColor = color;
	outUV = uv;
}