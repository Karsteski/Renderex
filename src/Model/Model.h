#pragma once

#include "ElementBuffer.h"
#include "VertexBuffer.h"
#include <string>

namespace Renderex {

class Model {
public:
    Model(std::string name, VertexBuffer vertex_buffer, ElementBuffer element_buffer);
    Model() = delete;

    std::string getName() const;
    const VertexBuffer& getVertexBuffer() const;
    const ElementBuffer& getElementBuffer() const;

private:
    std::string m_name;
    VertexBuffer m_vertex_buffer;
    ElementBuffer m_element_buffer;
};

}
