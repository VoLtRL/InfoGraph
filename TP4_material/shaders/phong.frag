#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
// AMBIENT
    float ambientStrength = 0.1; // Define a low constant strength
    vec3 ambient = ambientStrength * lightColor;
  
    // DIFFUSE 
    vec3 norm = normalize(Normal);
    // Calculate direction from fragment to light
    vec3 lightDir = normalize(LightPos - FragPos); 
    // Calculate impact of light based on angle (dot product)
    float diff = max(dot(norm, lightDir), 0.0); 
    vec3 diffuse = diff * lightColor;
    
    // SPECULAR
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos); // Viewer is at (0,0,0) in view-space
    
    vec3 reflectDir = reflect(-lightDir, norm);  
    
    // Calculate specular component
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
    // Combine all components and multiply by the object's color
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}