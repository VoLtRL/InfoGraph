#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;   // light position in world space

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
// ambient
    float ambientStrength = 0.1; // ambient intensity
    vec3 ambient = ambientStrength * lightColor; // ambient component
  
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos); // light direction
    float diff = max(dot(norm, lightDir), 0.0); // diffuse factor
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.4; // specular intensity
    vec3 viewDir = normalize(-FragPos); // direction from fragment to viewer
    
    vec3 reflectDir = reflect(-lightDir, norm); // direction of reflected light
    
    // Calculate specular component
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // shininess factor of 32
    vec3 specular = specularStrength * spec * lightColor;  
    
    // combine results
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}