#include "ShaderManager.h"

#include "Setup.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>

using namespace ::testing;

const std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

const std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        uniform vec4 rectangle_colour;

        void main()
        {
            FragColor = rectangle_colour;
        }
    )";

TEST(ShaderManagerFreeFunctions, LoadShaderReadsFileProperly)
{
    // Write a test_file
    const std::string filepath = "test_file.txt";
    std::ofstream output_file(filepath, std::ios::app);

    if (!output_file) {
        return;
    }

    const std::string line_1 = "first line";
    const std::string line_2 = "second line";
    output_file << line_1 << std::endl;
    output_file << line_2 << std::endl;

    // Read that same test_file
    const std::optional<std::string> file = Renderex::loadShader(filepath);

    std::istringstream file_ss(file.value());

    // Ensure that the first two lines read match the two lines written
    std::string line = "";
    std::getline(file_ss, line);
    EXPECT_THAT(line, Eq(line_1));
    std::getline(file_ss, line);
    EXPECT_THAT(line, Eq(line_2));

    // Tidy up test_file
    std::filesystem::remove(filepath);
}

TEST(ShaderManagerFreeFunctions, LoadShaderHandlesMissingFile)
{
    const std::string filepath = "file.txt";
    const std::optional<std::string> file = Renderex::loadShader(filepath);

    EXPECT_THAT(file.has_value(), Eq(false));
}

TEST(ShaderManager, CreateShaderReturnsIdOfShader)
{
    Renderex::ShaderManager shader_manager;

    const auto shader_id = shader_manager.createShader(Renderex::ShaderType::vertexShader, vertexShaderSource);

    const int glCreateShader_error_value = 0;
    EXPECT_THAT(shader_id.value(), Ne(glCreateShader_error_value));
}

TEST(ShaderManager, CreateShaderHandlesUncompiledShader)
{
    Renderex::ShaderManager shader_manager;

    const std::string bad_shader = "";
    const auto shader_id = shader_manager.createShader(Renderex::ShaderType::vertexShader, bad_shader);

    EXPECT_THAT(shader_id.has_value(), Eq(false));
}

TEST(ShaderManager, CompileShaderProgramReturnsIdOfCompiledProgram)
{
    Renderex::ShaderManager shader_manager;

    const auto vs_shader_id = shader_manager.createShader(Renderex::ShaderType::vertexShader, vertexShaderSource);
    const auto fs_shader_id = shader_manager.createShader(Renderex::ShaderType::fragmentShader, fragmentShaderSource);

    const auto shader_program_id = shader_manager.compileShaderProgram(vs_shader_id.value(), fs_shader_id.value());

    const int glCreateProgram_error_value = 0;
    EXPECT_THAT(shader_program_id.value(), Ne(glCreateProgram_error_value));
}

TEST(ShaderManager, CompileShaderProgramHandlesUncompiledShaderProgram)
{
    Renderex::ShaderManager shader_manager;

    const unsigned int bad_shader_id = 0;
    const auto shader_program_id = shader_manager.compileShaderProgram(bad_shader_id, bad_shader_id);

    EXPECT_THAT(shader_program_id.has_value(), Eq(false));
}
