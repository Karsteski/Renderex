#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Application {
    GLFWwindow* Initialize();
    void Run(GLFWwindow* window);
    int Exit(GLFWwindow* window);
}

