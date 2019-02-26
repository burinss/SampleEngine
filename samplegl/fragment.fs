#version 330 core
out vec4 FragColor;

in    vec3 FragPos;
in    vec2 TexCoords;
in    vec3 TangentLightPos;
in    vec3 TangentViewPos;
in    vec3 TangentFragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main()
{   
    vec3 normal = texture(texture_normal1, TexCoords).rgb;

    normal = normalize(normal * 2.0 - 1.0); 
	

    vec3 color = texture(texture_diffuse1, TexCoords).rgb;

    vec3 ambient = 0.2 * color;

    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
    vec3 specular = vec3(0.2) * spec * texture(texture_specular1, TexCoords).rgb;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
