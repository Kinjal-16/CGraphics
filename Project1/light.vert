#version 330 core

layout (location = 0) in vec3 aPos;
layout (location=1) in vec3 inNormal;
layout (location=2) in vec2 inTex;

uniform mat4 model;
uniform mat4 cameraM;
uniform float scale;
out vec2 Tex;
out vec3 Normal;
void main()
{
	gl_Position = cameraM*model * vec4(aPos*scale, 1.0f);
	Tex=inTex;
	Normal = inNormal;
};