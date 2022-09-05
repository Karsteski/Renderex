#pragma once

#include "VertexBufferLayout.h"

#include <string>
#include <vector>

class VertexBufferLayout;

class VertexBuffer {
public:
    VertexBuffer(std::string name, std::vector<float> data, VertexBufferLayout layout);

    std::string getName() const;
    unsigned int getID() const;
    const std::vector<float>& getData() const;
    unsigned int getSize() const; // TODO this should be named getNvertics or similar
    VertexBufferLayout getLayout() const;

private:
    std::string m_name;
    unsigned int m_vbo_ID;
    std::vector<float> m_data;
    VertexBufferLayout m_layout;
};
