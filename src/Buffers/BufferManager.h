#pragma once

#include "ElementBuffer.h"
#include "VertexBuffer.h"

#include <string>
#include <utility>
#include <vector>

class VertexBufferLayout;

enum class BufferType : int {
    Vertex,
    Element,
};

class BufferManager {
public:
    BufferManager();

    // Creates the VertexBuffer and its corresponding ElementBuffer from the data provided.
    // Returns the IDs as follows: first = VertexBuffer, second = ElementBuffer.
    std::pair<unsigned int, unsigned int> createModelBuffers(std::string name, std::vector<float> vertices, VertexBufferLayout layout, std::vector<unsigned int> elements);

    void bind(BufferType buffer, int ID);
    void unbind(BufferType buffer);

    const VertexBuffer& getVertexBuffer(unsigned int ID);
    const ElementBuffer& getElementBuffer(unsigned int ID);

    const std::vector<VertexBuffer>& getVertexBuffers();
    const std::vector<ElementBuffer>& getElementBuffers();

private:
    unsigned int m_vao;

    std::vector<VertexBuffer> m_vertex_buffers;
    std::vector<ElementBuffer> m_element_buffers;

    unsigned int m_bound_vbo;
    unsigned int m_bound_ebo;

    unsigned int m_fbo;

    void createVAO();

    unsigned int createVertexBuffer(std::string name, std::vector<float> vertices, VertexBufferLayout layout);
    unsigned int createElementBuffer(std::string name, std::vector<unsigned int> elements);
};
