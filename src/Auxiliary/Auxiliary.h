typedef unsigned int GLenum;

namespace Renderex {

// OpenGL Error Function
void GLDebugPrintMessage(GLenum source, GLenum type, unsigned int id, GLenum severity, int length, const char* message, const void* data);

}
