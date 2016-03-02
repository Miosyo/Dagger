#version 330 core

in vec4 outColor;
in vec2 outUV;

out vec3 color;

uniform sampler2D tex;

void main()
{
	color = texture(tex, outUV).rgb;// * outColor.rgb;
}