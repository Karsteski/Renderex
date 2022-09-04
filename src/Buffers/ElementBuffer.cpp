#include "ElementBuffer.h"

#include "GL/glew.h"

ElementBuffer::ElementBuffer(std::string name, std::vector<unsigned int> data)
    : m_name(name)
    , m_data(data)
{
    const int nBuffers = 1;
    glGenBuffers(nBuffers, &m_ebo_ID);
}

std::string ElementBuffer::getName() { return m_name; }

unsigned int ElementBuffer::getID() { return m_ebo_ID; }

int ElementBuffer::getNumberOfIndices() { return m_data.size(); }

int ElementBuffer::getNumberOfBytes() { return m_data.size() * sizeof(unsigned int); }

const std::vector<unsigned int>& ElementBuffer::getElements() { return m_data; }
