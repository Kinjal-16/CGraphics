#version 330 core

in vec2 Tex;
in vec3 Normal;
in vec3 currentPos;
struct DirLight {
    
	vec4 lightColor;
    
};
struct PointLight {
    
	vec4 lightColor;
	vec3 lightPos;
	
    
};
out vec4 FragColor;


uniform sampler2D tex0;
uniform vec3 cameraFrag;
uniform DirLight dirLight;
uniform PointLight point;


vec4 pointLight(PointLight light,vec3 Normal)
{	
	
	vec3 lightVec = light.lightPos - currentPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.5f;
	float b = 0.1f;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.05f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(cameraFrag - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return  texture(tex0,Tex)* light.lightColor * (diffuse+ambient+specular);
}

vec4 direcLight(DirLight light, vec3 Normal)
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(cameraFrag - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return  texture(tex0,Tex)* light.lightColor * (diffuse+ambient+specular);
}
void main()
{
	

	FragColor = direcLight(dirLight,Normal)+pointLight(point,Normal);
};