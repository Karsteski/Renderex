#include "Model.h"

namespace Renderex {
Model::Model(std ::string name, VertexBuffer vertex_buffer, ElementBuffer element_buffer)
    : m_name(name)
    , m_vertex_buffer(vertex_buffer)
    , m_element_buffer(element_buffer)
{
}

std::string Model::getName() const { return m_name; }

const VertexBuffer& Model::getVertexBuffer() const { return m_vertex_buffer; }

const ElementBuffer& Model::getElementBuffer() const { return m_element_buffer; }

}
