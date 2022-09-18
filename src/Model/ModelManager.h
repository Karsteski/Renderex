#pragma once
#include "ElementBuffer.h"
#include "Model.h"
#include "VertexBuffer.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

class VertexBufferLayout;

namespace Renderex {


enum class BufferType : int {
    Vertex,
    Element,
};

class ModelManager {
public:
    /*
     * TODO
     * Needs a bit of an API cleanup
     * createModelBuffers should instead return BufferManager's own id for each set of buffers
     * Calling bind on this id will set up the vertexAttribPointer as well as bind the corresponding vbo + ebo
     * Should be able to call a getBufferIDs() which returns a struct of vbo + ebo
     * Basically, the BufferManager public functions should work off its own model_id, and we just obtain the BufferIDs for drawing
     * */

    ModelManager();

    // Returns the id of the Model
    unsigned int createModel(std::string name, std::vector<float> vertices, VertexBufferLayout layout, std::vector<unsigned int> elements);

    bool removeModel(unsigned int model_id);

    const Model& getModel(unsigned int model_id) const;
    const std::map<unsigned int, Model>& getModels() const;

    void bind(unsigned int model_id);
    void unbind();

private:
    unsigned int m_vao = 0;

    unsigned int m_number_of_models = 0;
    std::map<unsigned int, Model> m_models;
    unsigned int m_bound_model_id = 0;

    // Core OpenGL requires a Vertex Array Object to know what to do with the vertices
    void createVAO();
};

}
