#version 330 core

in vec2 Tex;
in vec3 Normal;
in vec3 currentPos;


out vec4 FragColor;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform sampler2D tex0;
uniform vec3 cameraFrag;
void main()
{
	//Amnient lighting
	float ambient =0.3f;

	//Diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);


	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(cameraFrag - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;


	FragColor = texture(tex0,Tex)* lightColor * (diffuse+ambient+specular);
};