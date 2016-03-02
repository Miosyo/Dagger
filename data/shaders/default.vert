#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

out vec4 outColor;
out vec2 outUV;

void main()
{
    gl_Position = vec4(position, 1.0);
	outColor = color;
	outUV = uv;
}