#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;
float time;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);

    float theta = dot(lightDir, normalize(-light.direction));
    if (theta > light.cutOff)
    {
        //Ambient lighting
        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    
        //Compute diffuse lighting
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
        //Compute specular lighting
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specularTexel = texture(material.specular, TexCoords).rgb;
        vec3 specular = light.specular * spec * specularTexel;
        
        //Compute point light
        float distance = length(light.position - FragPos);
        float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);
    
        //Compute emission
        vec3 emission = (specularTexel == vec3(0.0))? texture(material.emission, TexCoords).rgb: vec3(0.0);
    
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
    
        vec3 result = ambient + diffuse + specular + emission;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
    }
    
}