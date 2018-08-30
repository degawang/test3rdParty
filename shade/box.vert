#version 330 core
layout (location = 0) in vec3 iPosition;
layout (location = 2) in vec2 iTexCoord;

out vec2 voTexCoord;

void main()
{
	gl_Position = vec4(iPosition, 1.0);
	voTexCoord = vec2(iTexCoord.x, iTexCoord.y);
}