#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D texture;
uniform bool useTexture;

uniform vec4 objectColor;
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
    vec4 color = objectColor;
    if (useTexture)
        color *= texture2D(texture, texCoord);

    // Ambient
    float ambientStrenght = 0.1;
    vec3 ambient = ambientStrenght * lightColor;

    // Diffuse
    float diffuseStrength = 1;
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = vec3(max(dot(lightDir, normal), 0)) * lightColor * diffuseStrength;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    FragColor = color * vec4(ambient + diffuse + specular, 1);
}
