#version 330 core

// Vertex Shader
#ifdef VERTEX_SHADER
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
#endif

// Fragment Shader
#ifdef FRAGMENT_SHADER
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform float time; // Time for animation
uniform float pulse_speed; // Speed of pulsing

void main()
{
    // Animated checkerboard pattern for error indication
    float scale = 8.0;
    float checker = mod(floor(TexCoords.x * scale) + floor(TexCoords.y * scale), 2.0);
    vec3 checkerColor = checker < 0.5 ? vec3(1.0, 0.0, 1.0) : vec3(0.0, 0.0, 0.0);
    
    // Pulsing effect
    float pulseIntensity = (sin(time * pulse_speed) * 0.5 + 0.5) * 0.5 + 0.5;
    
    // Mix with a glowing magenta color
    vec3 glowColor = vec3(1.0, 0.0, 1.0) * pulseIntensity;
    vec3 finalColor = mix(checkerColor, glowColor, 0.5);
    
    FragColor = vec4(finalColor, 1.0);
}
#endif
