#pragma once

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

std::string loadShader(std::string_view path);

class ShaderManager {
public:
    // For simplicity, ShaderManager curently only deals with a single vertex and fragment shader
    bool createShader(ShaderType shader_type, const std::string& shader);
    // Returns the ID of the compiled shader program
    unsigned int compileShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

    // Tell OpenGL to use this shader program
    bool bind(unsigned int shader_program_id);
    // Quit using the currently bound shader program
    void unbind();

private:
    std::vector<Shader> shaders;
    unsigned int shader_program_id;

    unsigned int createShaderProgram();
    std::optional<unsigned int> compileShader(ShaderType shader_type, const std::string& source);
    void attachShader(unsigned int shader_id, unsigned int shader_program_id);
};
}
