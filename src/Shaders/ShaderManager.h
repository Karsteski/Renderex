#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace Renderex {

struct Shader {
    std::string name;
    unsigned int id;
    std::string data;
};

enum class ShaderType : unsigned int;

std::optional<std::string> loadShader(std::filesystem::path path);

class ShaderManager {
public:
    ShaderManager(std::string_view vertex_shader_path, std::string_view fragment_shader_path);

    ShaderManager() = delete;

    // For simplicity, ShaderManager curently only deals with a single vertex and fragment shader
    std::optional<unsigned int> createShader(ShaderType shader_type, const std::string& shader);

    // Returns the ID of the compiled shader program
    unsigned int compileShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

    // Tell OpenGL to use this shader program
    void bind(unsigned int shader_program_id);

    // Quit using the currently bound shader program
    void unbind();

    bool shadersAvailable() const;

    unsigned int getID() const;

private:
    std::vector<Shader> m_shaders;
    unsigned int m_shader_program_id;
    bool m_shaders_available;

    std::optional<unsigned int> compileShader(ShaderType shader_type, const std::string& source);
};
}
