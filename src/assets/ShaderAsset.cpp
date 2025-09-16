#include "ShaderAsset.h"
#include <sstream>

std::string BasicShaderGenerator::generateCelVertexShader(int bands)
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << getCommonAttributes();
    ss << getCommonUniforms();
    ss << "\n";
    ss << "out vec3 FragPos;\n";
    ss << "out vec3 Normal;\n";
    ss << "out vec2 TexCoord;\n";
    ss << "out vec3 WorldPos;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    FragPos = vec3(uModel * vec4(aPos, 1.0));\n";
    ss << "    Normal = mat3(transpose(inverse(uModel))) * aNormal;\n";
    ss << "    TexCoord = aTexCoord;\n";
    ss << "    WorldPos = FragPos;\n";
    ss << "\n";
    ss << "    gl_Position = uProjection * uView * vec4(FragPos, 1.0);\n";
    ss << "}\n";

    return ss.str();
}

std::string BasicShaderGenerator::generateCelFragmentShader(int bands, bool outlineEnabled)
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << "in vec3 FragPos;\n";
    ss << "in vec3 Normal;\n";
    ss << "in vec2 TexCoord;\n";
    ss << "in vec3 WorldPos;\n";
    ss << "\n";
    ss << "out vec4 FragColor;\n";
    ss << "\n";
    ss << "uniform sampler2D uAlbedoTexture;\n";
    ss << "uniform vec3 uLightDirection;\n";
    ss << "uniform vec3 uLightColor;\n";
    ss << "uniform float uAmbientStrength;\n";
    ss << "uniform int uCelBands;\n";
    ss << "uniform bool uOutlineEnabled;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    // Sample albedo texture\n";
    ss << "    vec4 albedo = texture(uAlbedoTexture, TexCoord);\n";
    ss << "    \n";
    ss << "    // Calculate lighting\n";
    ss << "    vec3 norm = normalize(Normal);\n";
    ss << "    vec3 lightDir = normalize(-uLightDirection);\n";
    ss << "    \n";
    ss << "    // Cel-shading calculation\n";
    ss << "    float NdotL = max(dot(norm, lightDir), 0.0);\n";
    ss << "    \n";
    ss << "    // Quantize lighting into bands\n";
    ss << "    float celFactor = floor(NdotL * float(uCelBands)) / float(uCelBands);\n";
    ss << "    \n";
    ss << "    // Apply ambient and diffuse lighting\n";
    ss << "    vec3 ambient = uAmbientStrength * uLightColor;\n";
    ss << "    vec3 diffuse = celFactor * uLightColor;\n";
    ss << "    \n";
    ss << "    vec3 result = (ambient + diffuse) * albedo.rgb;\n";
    ss << "    \n";
    ss << "    FragColor = vec4(result, albedo.a);\n";
    ss << "}\n";

    return ss.str();
}

std::string BasicShaderGenerator::generateUnlitVertexShader()
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << getCommonAttributes();
    ss << getCommonUniforms();
    ss << "\n";
    ss << "out vec2 TexCoord;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    TexCoord = aTexCoord;\n";
    ss << "    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);\n";
    ss << "}\n";

    return ss.str();
}

std::string BasicShaderGenerator::generateUnlitFragmentShader()
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << "in vec2 TexCoord;\n";
    ss << "\n";
    ss << "out vec4 FragColor;\n";
    ss << "\n";
    ss << "uniform sampler2D uAlbedoTexture;\n";
    ss << "uniform vec4 uColor;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    vec4 texColor = texture(uAlbedoTexture, TexCoord);\n";
    ss << "    FragColor = texColor * uColor;\n";
    ss << "}\n";

    return ss.str();
}

std::unique_ptr<ShaderAsset> BasicShaderGenerator::createCelBandShader(const std::string &id,
                                                                       int bands,
                                                                       bool outlineEnabled)
{
    auto shader = std::make_unique<ShaderAsset>();

    shader->id = id;
    shader->path = "procedural://" + id; // Mark as procedurally generated
    shader->vertexSource = generateCelVertexShader(bands);
    shader->fragmentSource = generateCelFragmentShader(bands, outlineEnabled);

    // Set parameters
    shader->parameters["bands"] = std::to_string(bands);
    shader->parameters["outline_enabled"] = outlineEnabled ? "true" : "false";
    shader->parameters["specular_mode"] = "off";

    // Note: Actual compilation would happen in a rendering system
    shader->isCompiled = false;
    shader->programId = 0;

    return shader;
}

std::string BasicShaderGenerator::getCommonUniforms()
{
    std::ostringstream ss;
    ss << "uniform mat4 uModel;\n";
    ss << "uniform mat4 uView;\n";
    ss << "uniform mat4 uProjection;\n";
    return ss.str();
}

std::string BasicShaderGenerator::getCommonAttributes()
{
    std::ostringstream ss;
    ss << "layout (location = 0) in vec3 aPos;\n";
    ss << "layout (location = 1) in vec3 aNormal;\n";
    ss << "layout (location = 2) in vec2 aTexCoord;\n";
    return ss.str();
}


