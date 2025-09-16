#include "BasicShaderGenerator.h"
#include <sstream>
#include <algorithm>
#include "../debug.h"

ShaderInfo BasicShaderGenerator::generateShader(const std::string &shaderType,
                                                const std::map<std::string, std::string> &parameters)
{
    DEBUG_LOG("Generating shader of type '" + shaderType + "'");
    if (shaderType == "phong")
    {
        return generatePhongShader(parameters);
    }
    else if (shaderType == "pbr")
    {
        return generatePBRShader(parameters);
    }
    else if (shaderType == "unlit")
    {
        return generateUnlitShader(parameters);
    }
    else if (shaderType == "debug")
    {
        return generateDebugShader(parameters);
    }
    else
    {
        // Default to unlit
        return generateUnlitShader(parameters);
    }
}

ShaderInfo BasicShaderGenerator::generatePhongShader(const std::map<std::string, std::string> &parameters)
{
    DEBUG_LOG("Generating Phong shader");
    ShaderInfo shader;

    // Vertex shader
    shader.vertexSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal;
    TexCoord = aTexCoord;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

    // Fragment shader
    std::ostringstream fragShader;
    fragShader << R"(
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

// Material properties
uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform float material_shininess;
uniform sampler2D material_diffuseMap;
uniform bool material_useDiffuseMap;

// Light properties
uniform vec3 light_position;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;

// View position
uniform vec3 viewPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    // Ambient
    vec3 ambient = light_ambient * material_ambient;
    
    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse_color = material_useDiffuseMap ? 
        texture(material_diffuseMap, TexCoord).rgb : material_diffuse;
    vec3 diffuse = light_diffuse * diff * diffuse_color;
    
    // Specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
    vec3 specular = light_specular * spec * material_specular;
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
)";

    shader.fragmentSource = fragShader.str();

    // Set up uniforms
    shader.uniforms = {
        "model", "view", "projection", "normalMatrix", "viewPos",
        "material_ambient", "material_diffuse", "material_specular",
        "material_shininess", "material_diffuseMap", "material_useDiffuseMap",
        "light_position", "light_ambient", "light_diffuse", "light_specular"};

    shader.attributes = {"aPos", "aNormal", "aTexCoord"};

    return shader;
}

ShaderInfo BasicShaderGenerator::generatePBRShader(const std::map<std::string, std::string> &parameters)
{
    DEBUG_LOG("Generating PBR shader");
    ShaderInfo shader;

    // Basic PBR vertex shader
    shader.vertexSource = generateVertexShader(true, true, false);

    // PBR fragment shader with simplified model
    shader.fragmentSource = R"(
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

// PBR material properties
uniform vec3 albedo;
uniform float roughness;
uniform float metallic;
uniform float ao;
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform bool useAlbedoMap;
uniform bool useNormalMap;
uniform bool useMetallicMap;
uniform bool useRoughnessMap;
uniform bool useAOMap;

// Lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];
uniform int numLights;

uniform vec3 camPos;

const float PI = 3.14159265359;

vec3 getNormalFromMap()
{
    if (!useNormalMap)
        return normalize(Normal);
        
    vec3 tangentNormal = texture(normalMap, TexCoord).xyz * 2.0 - 1.0;
    
    vec3 Q1 = dFdx(FragPos);
    vec3 Q2 = dFdy(FragPos);
    vec2 st1 = dFdx(TexCoord);
    vec2 st2 = dFdy(TexCoord);
    
    vec3 N = normalize(Normal);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);
    
    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
    
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;
    
    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{
    vec3 albedoColor = useAlbedoMap ? texture(albedoMap, TexCoord).rgb : albedo;
    float metallicValue = useMetallicMap ? texture(metallicMap, TexCoord).r : metallic;
    float roughnessValue = useRoughnessMap ? texture(roughnessMap, TexCoord).r : roughness;
    float aoValue = useAOMap ? texture(aoMap, TexCoord).r : ao;
    
    vec3 N = getNormalFromMap();
    vec3 V = normalize(camPos - FragPos);
    
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedoColor, metallicValue);
    
    vec3 Lo = vec3(0.0);
    for(int i = 0 i < numLights && i < 4; ++i)
    {
        vec3 L = normalize(lightPositions[i] - FragPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions[i] - FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors[i] * attenuation;
        
        float NDF = DistributionGGX(N, H, roughnessValue);
        float G = GeometrySmith(N, V, L, roughnessValue);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallicValue;
        
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;
        
        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedoColor / PI + specular) * radiance * NdotL;
    }
    
    vec3 ambient = vec3(0.03) * albedoColor * aoValue;
    vec3 color = ambient + Lo;
    
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // Gamma correction
    color = pow(color, vec3(1.0/2.2));
    
    FragColor = vec4(color, 1.0);
}
)";

    shader.uniforms = {
        "model", "view", "projection", "normalMatrix", "camPos",
        "albedo", "roughness", "metallic", "ao",
        "albedoMap", "normalMap", "metallicMap", "roughnessMap", "aoMap",
        "useAlbedoMap", "useNormalMap", "useMetallicMap", "useRoughnessMap", "useAOMap",
        "lightPositions", "lightColors", "numLights"};

    shader.attributes = {"aPos", "aNormal", "aTexCoord"};

    return shader;
}

ShaderInfo BasicShaderGenerator::generateUnlitShader(const std::map<std::string, std::string> &parameters)
{
    DEBUG_LOG("Generating unlit shader");
    ShaderInfo shader;

    shader.vertexSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

    shader.fragmentSource = R"(
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 color;
uniform sampler2D mainTexture;
uniform bool useTexture;

void main()
{
    vec3 finalColor = useTexture ? texture(mainTexture, TexCoord).rgb * color : color;
    FragColor = vec4(finalColor, 1.0);
}
)";

    shader.uniforms = {"model", "view", "projection", "color", "mainTexture", "useTexture"};
    shader.attributes = {"aPos", "aTexCoord"};

    return shader;
}

ShaderInfo BasicShaderGenerator::generateDebugShader(const std::map<std::string, std::string> &parameters)
{
    DEBUG_LOG("Generating debug shader");
    ShaderInfo shader;

    auto debugType = parameters.find("debug_type");
    std::string type = (debugType != parameters.end()) ? debugType->second : "normals";

    shader.vertexSource = generateVertexShader(true, true, false);

    if (type == "normals")
    {
        shader.fragmentSource = R"(
#version 330 core

in vec3 Normal;
out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);
    FragColor = vec4(norm * 0.5 + 0.5, 1.0);
}
)";
    }
    else if (type == "uvs")
    {
        shader.fragmentSource = R"(
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
    FragColor = vec4(TexCoord, 0.0, 1.0);
}
)";
    }
    else
    {
        // Default wireframe-style debug
        shader.fragmentSource = R"(
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
)";
    }

    shader.uniforms = {"model", "view", "projection", "normalMatrix"};
    shader.attributes = {"aPos", "aNormal", "aTexCoord"};

    return shader;
}

std::vector<std::string> BasicShaderGenerator::getSupportedShaderTypes()
{
    return {"phong", "pbr", "unlit", "debug"};
}

std::string BasicShaderGenerator::generateVertexShader(bool includeNormals, bool includeUVs, bool includeColors)
{
    DEBUG_LOG("Generating vertex shader with normals=" + std::to_string(includeNormals)+ ", UVs=" + std::to_string(includeUVs) + ", colors=" + std::to_string(includeColors))
    std::ostringstream vs;

    vs << "#version 330 core\n\n";
    vs << "layout (location = 0) in vec3 aPos;\n";

    if (includeNormals)
    {
        vs << "layout (location = 1) in vec3 aNormal;\n";
        vs << "out vec3 FragPos;\n";
        vs << "out vec3 Normal;\n";
    }

    if (includeUVs)
    {
        vs << "layout (location = 2) in vec2 aTexCoord;\n";
        vs << "out vec2 TexCoord;\n";
    }

    if (includeColors)
    {
        vs << "layout (location = 3) in vec3 aColor;\n";
        vs << "out vec3 VertexColor;\n";
    }

    vs << "\nuniform mat4 model;\n";
    vs << "uniform mat4 view;\n";
    vs << "uniform mat4 projection;\n";

    if (includeNormals)
    {
        vs << "uniform mat3 normalMatrix;\n";
    }

    vs << "\nvoid main()\n{\n";

    if (includeNormals)
    {
        vs << "    FragPos = vec3(model * vec4(aPos, 1.0));\n";
        vs << "    Normal = normalMatrix * aNormal;\n";
    }

    if (includeUVs)
    {
        vs << "    TexCoord = aTexCoord;\n";
    }

    if (includeColors)
    {
        vs << "    VertexColor = aColor;\n";
    }

    vs << "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n";
    vs << "}\n";

    return vs.str();
}

std::string BasicShaderGenerator::generateLightingCode(const std::string &lightingModel)
{
    if (lightingModel == "phong")
    {
        return R"(
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    vec3 ambient = light_ambient * material_ambient;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light_diffuse * diff * material_diffuse;
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_shininess);
    vec3 specular = light_specular * spec * material_specular;
    
    vec3 result = ambient + diffuse + specular;
)";
    }

    return "    vec3 result = vec3(1.0);\n";
}

std::string BasicShaderGenerator::generateUniforms(const std::map<std::string, std::string> &parameters)
{
    std::ostringstream uniforms;

    for (const auto &[key, value] : parameters)
    {
        if (key.find("color") != std::string::npos)
        {
            uniforms << "uniform vec3 " << key << ";\n";
        }
        else if (key.find("texture") != std::string::npos)
        {
            uniforms << "uniform sampler2D " << key << ";\n";
        }
        else if (key.find("float") != std::string::npos || key.find("roughness") != std::string::npos || key.find("metallic") != std::string::npos)
        {
            uniforms << "uniform float " << key << ";\n";
        }
    }

    return uniforms.str();
}

std::vector<float> BasicShaderGenerator::parseColor(const std::string &colorStr,
                                                    const std::vector<float> &defaultColor)
{
    std::vector<float> color = defaultColor;

    if (colorStr.empty())
        return color;

    std::istringstream iss(colorStr);
    std::string component;
    size_t index = 0;

    while (std::getline(iss, component, ',') && index < color.size())
    {
        try
        {
            color[index] = std::stof(component);
            index++;
        }
        catch (const std::exception &)
        {
            break;
        }
    }

    return color;
}



