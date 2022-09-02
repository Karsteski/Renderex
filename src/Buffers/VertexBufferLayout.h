#pragma once

#include <GL/glew.h>
#include <cstddef>
#include <vector>
#include <string>

struct VertexBufferElement {
    // TODO Add name for each elements
    std::string name;
    uint32_t type;
    uint32_t count;

    // unsigned char rather than bool to avoid Glboolean conversion.
    unsigned char normalized;

    static uint32_t getSizeOfType(uint32_t type)
    {
        // clang-format off
        switch (type)
        {
            case GL_FLOAT:          return sizeof(float);
            case GL_UNSIGNED_INT:   return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE:  return sizeof(unsigned char);
        }
        // clang-format on

        return 0;
    }
};

// Maintains elements in the Vertex Buffer, specifying the layout of the buffer.
// Index of element is the index in the m_Elements std::vector.
class VertexBufferLayout {
public:
    VertexBufferLayout()
        : m_Stride(0) {};

    template <typename T>
    // Explicitly prevent unspecified function from being called.
    // Templates are outside class as C++ standard does not allow for explicit template specialization
    // in a non-namespace scope.
    void push(std::string name, uint32_t count) = delete;

    // Long explanation, see: http://docs.gl/gl4/glVertexAttribPointer
    inline uint32_t getStride() const
    {
        return m_Stride;
    }

    inline const std::vector<VertexBufferElement> getElements() const
    {
        return m_Elements;
    }

private:
    std::vector<VertexBufferElement> m_Elements;

    uint32_t m_Stride;
};

// Specializations for each type of element.
template <>
inline void VertexBufferLayout::push<float>(std::string name, uint32_t count)
{
    m_Elements.push_back({ name, GL_FLOAT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::push<uint32_t>(std::string name, uint32_t count)
{
    m_Elements.push_back({ name, GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::push<unsigned char>(std::string name, uint32_t count)
{
    m_Elements.push_back({ name, GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
