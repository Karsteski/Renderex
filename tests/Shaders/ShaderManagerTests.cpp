#include "ShaderManager.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <fstream>
#include <sstream>
#include <filesystem>

using namespace ::testing;

TEST(ShaderManagerFreeFunctions, LoadShaderReadsFileCorrectly)
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
    const std::string file = Renderex::loadShader(filepath);
    std::istringstream file_ss(file);

    // Ensure that the first two lines read match the two lines written
    std::string line = "";
    std::getline(file_ss, line);
    EXPECT_THAT(line, Eq(line_1));
    std::getline(file_ss, line);
    EXPECT_THAT(line, Eq(line_2));

    // Tidy up test_file
    std::filesystem::remove(filepath);
}
