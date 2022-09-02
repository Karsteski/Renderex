#pragma once

#include "VertexBufferLayout.h"

#include <string>
#include <vector>

class VertexBufferLayout;

class VertexBuffer {
public:
    VertexBuffer(std::string name, std::vector<float> data, VertexBufferLayout layout);

    std::string getName();
    unsigned int getID();
    std::vector<float> getData(); // TODO should just return a const ref 
    VertexBufferLayout getLayout();

private:
    std::string m_name;
    unsigned int m_vbo_ID;
    std::vector<float> m_data;
    VertexBufferLayout m_layout;
};
