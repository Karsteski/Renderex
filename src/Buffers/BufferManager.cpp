#include "BufferManager.h"

#include "VertexBuffer.h"

#include "GL/glew.h"

#include <algorithm>

BufferManager::BufferManager()
{
    createVAO();
}

std::pair<unsigned int, unsigned int> BufferManager::createModelBuffers(std::string name, std::vector<float> vertices, VertexBufferLayout layout, std::vector<unsigned int> elements)
{
    unsigned int vbo_ID = createVertexBuffer(name, vertices, layout);
    unsigned int ebo_ID = createElementBuffer(name, elements);

    return { vbo_ID, ebo_ID };
}

void BufferManager::bind(BufferType buffer, int ID)
{
    switch (buffer) {
    case BufferType::Vertex:
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        m_bound_vbo = ID;
        break;
    case BufferType::Element:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        m_bound_ebo = ID;
        break;
    }
}

void BufferManager::unbind(BufferType buffer)
{
    switch (buffer) {
    case BufferType::Vertex:
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_bound_vbo = 0;
        break;
    case BufferType::Element:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        m_bound_ebo = 0;
        break;
    }
}

const VertexBuffer& BufferManager::getVertexBuffer(unsigned int ID) const
{
    auto matches_ID = [=](VertexBuffer vbo) -> bool {
        return vbo.getID() == ID;
    };

    // const auto matching_vbo = std::find_if(m_vertex_buffers.begin(), m_vertex_buffers.end(), matches_ID);
    // return *matching_vbo;
    return m_vertex_buffers[0];
}

const ElementBuffer& BufferManager::getElementBuffer(unsigned int ID) const
{
    auto matches_ID = [=](ElementBuffer ebo) -> bool {
        return ebo.getID() == ID;
    };

    // const auto matching_ebo = std::find_if(m_element_buffers.begin(), m_element_buffers.end(), matches_ID);
    // return *matching_ebo;
    return m_element_buffers[0];
}

const std::vector<VertexBuffer>& BufferManager::getVertexBuffers() const
{
    return m_vertex_buffers;
}

const std::vector<ElementBuffer>& BufferManager::getElementBuffers() const
{
    return m_element_buffers;
}

void BufferManager::createVAO()
{
    const int nBuffers = 1;
    glGenVertexArrays(nBuffers, &m_vao);
    glBindVertexArray(m_vao);
};

unsigned int BufferManager::createVertexBuffer(std::string name, std::vector<float> vertices, VertexBufferLayout layout)
{
    std::string vbo_name = name + "_vbo";
    VertexBuffer vertex_buffer(vbo_name, vertices, layout);
    m_vertex_buffers.push_back(vertex_buffer);

    return vertex_buffer.getID();
}

unsigned int BufferManager::createElementBuffer(std::string name, std::vector<unsigned int> elements)
{
    std::string ebo_name = name + "_ebo";
    ElementBuffer element_buffer(ebo_name, elements);
    m_element_buffers.push_back(element_buffer);

    return element_buffer.getID();
}
