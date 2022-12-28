#version 330 core
layout (location = 0) in vec3 aPos;
layout (location=1) in vec3 inNormal;
layout (location=2) in vec2 inTex;

out vec2 Tex;
uniform mat4 cameraM; 
uniform float scale;

out vec3 Normal;
uniform mat4 model;
out vec3 currentPos;
void main()
{
	gl_Position = cameraM * model*vec4(aPos*scale , 1.0);
	currentPos = vec3(model * vec4(aPos, 1.0f));
	Tex=inTex;
	Normal = inNormal;
};