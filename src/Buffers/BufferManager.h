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

// TODO Should I find a way to only have one of these?
class BufferManager {
public:
    /* 
     * TODO
     * Needs a bit of an API cleanup
     * createModelBuffers should instead return BufferManager's own id for each set of buffers
     * Calling bind on this id will set up the vertexAttribPointer as well as bind the corresponding vbo + ebo
     * Should be able to call a getBufferIDs() which returns a struct of vbo + ebo
     * Basically, the BufferManager public functions should work off its own model_id, and we just obtain the BufferIDs for drawing
     * */


    BufferManager();

    // Creates the VertexBuffer and its corresponding ElementBuffer from the data provided.
    // Returns the IDs as follows: first = VertexBuffer, second = ElementBuffer.
    std::pair<unsigned int, unsigned int> createModelBuffers(std::string name, std::vector<float> vertices, VertexBufferLayout layout, std::vector<unsigned int> elements);

    void bind(BufferType buffer, int ID);
    void unbind(BufferType buffer);

    const VertexBuffer& getVertexBuffer(unsigned int ID) const;
    const ElementBuffer& getElementBuffer(unsigned int ID) const;

    const std::vector<VertexBuffer>& getVertexBuffers() const;
    const std::vector<ElementBuffer>& getElementBuffers() const;

private:
    unsigned int m_vao;

    std::vector<VertexBuffer> m_vertex_buffers;
    std::vector<ElementBuffer> m_element_buffers;

    unsigned int m_bound_vbo;
    unsigned int m_bound_ebo;

    unsigned int m_fbo;

    // Core OpenGL requires a Vertex Array Object to know what to do with the vertices
    void createVAO();

    unsigned int createVertexBuffer(std::string name, std::vector<float> vertices, VertexBufferLayout layout);
    unsigned int createElementBuffer(std::string name, std::vector<unsigned int> elements);
};
