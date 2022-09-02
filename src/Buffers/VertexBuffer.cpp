#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

// GLEW loads OpenGL function pointers from the system's graphics drivers.
// glew.h MUST be included before gl.h
// clang-format off
// For OpenGL functions
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

VertexBuffer::VertexBuffer(std::string name, std::vector<float> data, VertexBufferLayout layout)
    : m_name(name)
    , m_data(data)
    , m_layout(layout)
{
    const int nBuffers = 1;
    glGenBuffers(nBuffers, &m_vbo_ID);
};

std::string VertexBuffer::getName()
{
    return m_name;
}

unsigned int VertexBuffer::getID()
{
    return m_vbo_ID;
}

std::vector<float> VertexBuffer::getData()
{
    return m_data;
}

VertexBufferLayout VertexBuffer::getLayout()
{
    return m_layout;
}
