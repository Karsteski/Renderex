#include "ModelManager.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "GL/glew.h"

#include <algorithm>

namespace Renderex {

ModelManager::ModelManager()
{
    createVAO();
}

unsigned int ModelManager::createModel(std::string name, std::vector<float> vertices, VertexBufferLayout layout, std::vector<unsigned int> elements)
{
    const VertexBuffer vertex_buffer(name, vertices, layout);
    const ElementBuffer element_buffer(name, elements);
    const Model model(name, vertex_buffer, element_buffer);

    const unsigned int model_id = m_number_of_models;
    // m_models[model_id] = model;
    m_models.insert({model_id, model});
    ++m_number_of_models;

    return model_id;
}

bool ModelManager::removeModel(unsigned int model_id) { return false; }

const Model& ModelManager::getModel(unsigned int model_id) const
{
    return m_models.at(model_id);
}

const std::map<unsigned int, Model>& ModelManager::getModels() const { }

void ModelManager::bind(unsigned int model_id)
{
    auto model = getModel(model_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.getElementBuffer().getID());
    glBindBuffer(GL_ARRAY_BUFFER, model.getVertexBuffer().getID());

    m_bound_model_id = model_id;
}

void ModelManager::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    m_bound_model_id = 0;
}

void ModelManager::createVAO()
{
    const int nBuffers = 1;
    glGenVertexArrays(nBuffers, &m_vao);
    glBindVertexArray(m_vao);
};

}
