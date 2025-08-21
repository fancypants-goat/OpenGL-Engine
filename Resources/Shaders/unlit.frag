#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D texture;
uniform bool useTexture;

uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objAmbient;
uniform vec3 objDiffuse;
uniform vec3 objSpecular;
uniform float specularExp;
uniform vec3 objColor;

void main()
{
    vec4 color = vec4(objColor, 1);
    if (useTexture)
        color *= texture2D(texture, texCoord);

    // Ambient
    float ambientStrenght = 0.4;
    vec3 ambient = ambientStrenght * lightColor * objAmbient;

    // Diffuse
    float diffuseStrength = 1;
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = vec3(max(dot(lightDir, normal), 0)) * lightColor * objDiffuse * diffuseStrength;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), specularExp);
    vec3 specular = specularStrength * spec * lightColor * objSpecular;

    FragColor = color * vec4(ambient + diffuse + specular, 1);
}
