#version 330 core
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_diffuse2;
    sampler2D texture_specular2;
    sampler2D emission;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointlights[NR_POINT_LIGHTS];

uniform DirectionalLight dirLight;

uniform SpotLight spotlight;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;

uniform Material material;

float time;

vec3 computeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 computePointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir);
vec3 computeSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lighting = computeDirectionalLight(dirLight, norm, viewDir);

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        lighting += computePointLight(pointlights[i], norm, FragPos, viewDir);
    }
    lighting += computeSpotLight(spotlight, norm, FragPos, viewDir);

    FragColor = vec4(lighting, 1.0);
}

//Compute lighting for a directional light;
vec3 computeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    //Ambient lighting
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //Compute diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    //Compute specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTexel = texture(material.specular, TexCoords).rgb;
    vec3 specular = light.specular * spec * specularTexel;

    //Compute emission
    //vec3 emission = (specularTexel == vec3(0.0))? texture(material.emission, TexCoords).rgb: vec3(0.0);

    return (ambient + diffuse + specular);

}

vec3 computePointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - FragPos);

    //Ambient lighting
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //Compute diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    //Compute specular lighting

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTexel = texture(material.specular, TexCoords).rgb;
    vec3 specular = light.specular * spec * specularTexel;

    //Compute point light
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);

    //Compute emission
    //vec3 emission = (specularTexel == vec3(0.0))? texture(material.emission, TexCoords).rgb: vec3(0.0);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);

}
vec3 computeSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - FragPos);

    float theta = dot(lightDir, normalize(-light.direction));
    float espilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / espilon, 0.0, 1.0);

    //Ambient lighting
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //Compute diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    //Compute specular lighting

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTexel = texture(material.specular, TexCoords).rgb;
    vec3 specular = light.specular * spec * specularTexel;
    
    //Intensity modifier
    diffuse *= intensity;
    specular *= intensity;

    //Compute point light
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);

    //Compute emission
    //vec3 emission = (specularTexel == vec3(0.0))? texture(material.emission, TexCoords).rgb: vec3(0.0);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
