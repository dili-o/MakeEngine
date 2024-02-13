#version 330 core

out vec4 FragColor;

in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec3 u_ViewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

void main()
{
    // Ambient light
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));

    // Difuse light
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(-light.direction); 
    float diffuseImpact = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diffuseImpact * vec3(texture(material.diffuse, v_TexCoord));

    // Specular light
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 halfwayDir = normalize((lightDir + viewDir) / 2.0);
    float spec = pow(max(dot(halfwayDir, norm), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, v_TexCoord)));
    
    // Add all the light components together
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}
