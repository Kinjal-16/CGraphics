#version 330 core
in vec3 colour;
in vec2 Tex;
out vec4 FragColor;
uniform sampler2D tex0;
void main()
{
   FragColor = texture(tex0,Tex);
};