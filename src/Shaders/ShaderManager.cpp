#include "ShaderManager.h"

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace Renderex {

std::string loadShader(std::string_view path)
{
    std::ifstream stream(path.data());
    std::string line = "";

    std::stringstream string_stream;

    while (std::getline(stream, line)) {
        string_stream << line << std::endl;
    }

    return string_stream.str();
}

enum class ShaderType : unsigned int {
    vertexShader = GL_VERTEX_SHADER,
    fragmentShader = GL_FRAGMENT_SHADER
};

ShaderManager::ShaderManager(std::string_view vertex_shader_path, std::string_view fragment_shader_path)
    : m_shaders_available(false)
{
    const std::optional<unsigned int> vertex_shader = createShader(ShaderType::vertexShader, vertex_shader_path.data());
    const std::optional<unsigned int> fragment_shader = createShader(ShaderType::fragmentShader, fragment_shader_path.data());

    if (vertex_shader.has_value() and fragment_shader.has_value()) {
        const unsigned int program_id = compileShaderProgram(vertex_shader.value(), fragment_shader.value());

        bind(program_id);

        m_shaders_available = true;
    } else {
        m_shaders_available = false;
    }
}

std::optional<unsigned int> ShaderManager::createShader(ShaderType shader_type, const std::string& shader)
{

    std::optional<unsigned int> compiled_shader_id = compileShader(shader_type, shader);

    if (compiled_shader_id == std::nullopt) {
        return false;
    }

    return true;
}

unsigned int ShaderManager::compileShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id)
{
    unsigned int program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    glValidateProgram(program_id);

    // Delete to shaders once they have been linked and compiled.
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

void ShaderManager::bind(unsigned int shader_program_id)
{
    glUseProgram(shader_program_id);
}

void ShaderManager::unbind()
{
    glUseProgram(0);
}

bool ShaderManager::shadersAvailable()
{
    return m_shaders_available;
}

std::optional<unsigned int> ShaderManager::compileShader(ShaderType shader_type, const std::string& source)
{
    unsigned int id = glCreateShader(static_cast<unsigned int>(shader_type));

    const int nShaderSources = 1;
    const char* src = source.c_str();
    // Note that strings must be null-terminated if passing length as nullptr
    glShaderSource(id, nShaderSources, &src, nullptr);
    glCompileShader(id);

    // Error handling.
    int result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int errorMessageLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorMessageLength);
        std::string message = "";
        glGetShaderInfoLog(id, errorMessageLength, &errorMessageLength, message.data());

        // A bit hacky, will eventually need proper logging.
        std::cout << "Failed to compile " << (shader_type == ShaderType::vertexShader ? "vertex" : "fragment") << " shader!\n"
                  << message << std::endl;

        glDeleteShader(id);

        return std::nullopt;
    }

    return id;
}

bool ShaderManager::attachShader(unsigned int shader_id, unsigned int shader_program_id)
{
    if (shader_program_id != 0) {
        glAttachShader(shader_program_id, shader_id);
        return true;
    }

    return false;
}
}
