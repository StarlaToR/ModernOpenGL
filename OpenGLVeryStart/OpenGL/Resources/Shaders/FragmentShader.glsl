#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourNormal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2; 

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 lightPos;
uniform vec3 lightDirection;
uniform int lightType;

uniform vec3 viewPos;

void main()
{
	//ambient
	vec3 ambient = ambientColor;

	//diffuse
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColor;

	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * specularColor;

	//final
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5) * vec4(ambient + diffuse + specular, 1.0);
};