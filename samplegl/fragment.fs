#version 330 core
out vec4 FragColor;

in    vec3 FragPos;
in    vec2 TexCoords;
in    vec3 TangentLightPos;
in    vec3 TangentViewPos;
in    vec3 TangentFragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform float lightRadius;
uniform float compression;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;


void main()
{   
	//float depth = LinearizeDepth(gl_FragCoord.z) / far;

    vec3 normal = texture(texture_normal1, TexCoords).rgb;

    normal = normalize(normal * 2.0 - 1.0);

    vec3 color =texture(texture_diffuse1, TexCoords).rgb;

    vec3 ambient = 0.01 * color;

    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
	float attenuation = pow(smoothstep(lightRadius, 0, length(lightPos - FragPos)), compression);
    vec3 diffuse = diff * color * attenuation;

    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 128);
    vec3 specular = vec3(1.01) * spec * texture(texture_specular1, TexCoords).rgb;
    
	
	FragColor = vec4(color, 1.0);
	//FragColor = vec4((ambient + diffuse + specular)*lightColor, 1.0);
}
