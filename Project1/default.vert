#version 330 core
layout (location = 0) in vec3 aPos;
layout (location=1) in vec3 incolour;
layout (location=2) in vec2 inTex;
out vec3 colour;
out vec2 Tex;
uniform mat4 cameraM; 
uniform float scale;
void main()
{
	gl_Position = cameraM * vec4(aPos*scale , 1.0);
	colour=incolour;
	Tex=inTex;
};