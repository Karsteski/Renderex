// GLEW loads OpenGL function pointers from the system's graphics drivers.
// glew.h MUST be included before gl.h
// clang-format off
// For OpenGL functions
#include <GL/glew.h>
#include <GL/gl.h>

// Window and input management
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// clang-format on

namespace Renderex {

// OpenGL Error Function
void APIENTRY GLDebugPrintMessage(GLenum source, GLenum type, unsigned int id, GLenum severity, int length, const char* message, const void* data);

}
