#version 330 core
in vec2 Tex;
in vec3 Normal;
out vec4 FragColor;

uniform vec4 lightColor;
uniform sampler2D tex0;
void main()
{
	FragColor = texture(tex0,Tex)* lightColor ;
}