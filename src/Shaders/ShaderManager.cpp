#include "ShaderManager.h"

#include <string>
#include <fstream>
#include <sstream>

std::string Renderex::loadShader(std::string path){
    std::ifstream stream(path);
    std::string line = "";

    std::stringstream string_stream;

    while (std::getline(stream, line)) {
        string_stream << line << std::endl;
    }

    return string_stream.str();
}
