#version 460
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 aPos;
} vs_out;

uniform vec3 lightPos;
uniform vec3 modelColor;
uniform float playerScale;
uniform vec3 viewPos;
uniform vec3 offset;
uniform vec3 view;

void main()
{
    vec3 FragPos = vs_out.FragPos;

    float scaleFactor = 1.0f;

    vec3 fragColor = modelColor;

    float ambientStrength = 0.001f;
    vec3 ambient = ambientStrength * vec3(1.0f);

    vec3 norm = normalize(vs_out.Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);

    float distance = length(lightPos - FragPos);
    float attenuation = 1.0f / (0.05 * distance * distance);

    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f) * attenuation;

    float specularStrength = 0.01f;

    vec3 viewDir = normalize(viewPos - vs_out.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);

    vec3 specular = specularStrength * spec * vec3(1.0f);

    vec3 result = (ambient + diffuse + specular) * fragColor;

    float gamma = 2.2f;
    FragColor = vec4(pow(result, vec3(1.0f/gamma)), 1.0f);
}
