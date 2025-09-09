#include "Auxiliary.h"
#include "ModelManager.h"
#include "ShaderManager.h"

// GLEW loads OpenGL function pointers from the system's graphics drivers.
// glew.h MUST be included before gl.h
// clang-format off
// For OpenGL functions
#include <GL/glew.h>
#include <GL/gl.h>

// Window and input management
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// clang-format on

// DearImGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Maths Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{

    // ----------------------
    // So much boilerplate
    // ----------------------

    // GLFW Setup
    if (!glfwInit()) {
        std::cout << "GLFW Initialization failed!\n"
                  << "Exiting...\n";

        exit(EXIT_FAILURE);
    }

    // OpenGL version and mode setup.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // GLFW Window settings
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // For OpenGL debugging.
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    const int initialWindowWidth = 800;
    const int initialWindowHeight = 600;

    auto* window = glfwCreateWindow(initialWindowWidth, initialWindowHeight, "Oglre", nullptr, nullptr);
    if (!window) {
        std::cout << "GLFW Window creation failed\n"
                  << "Exiting...\n";

        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // A valid OpenGL context must be created before initializing GLEW.
    // Initialize OpenGL loader (GLEW in this project).
    bool error = glewInit();
    if (error != GLEW_OK) {
        std::cout << "Error: Failed to initialize OpenGL function pointer loader!\n";
    }

    // Enable debugging layer of OpenGL
    int glFlags = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &glFlags);
    if (glFlags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(Renderex::GLDebugPrintMessage, nullptr);

        std::cout << ("OpenGL Debug Mode\n");
    } else {
        std::cout << "Debug for OpenGL not supported by the system!\n";
    }

    // Printing OpenGL version for convenience.
    std::cout << "OpenGL Version + System GPU Drivers: " << glGetString(GL_VERSION) << std::endl;

    // DearImGUI setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    const std::string_view glsl_version = "#version 330";

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.data());

    // ----------------------
    // Relevant OpenGL Code
    // ----------------------

    Renderex::ModelManager model_manager;
    const int nBuffers = 1;
    std::vector<float> vertices = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top lef
    };

    VertexBufferLayout layout;
    const int nFloatsPerAttribute = 3;
    layout.push<float>("position", nFloatsPerAttribute);

    // Set up element buffer object
    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    const unsigned int model_id = model_manager.createModel("rectangle", vertices, layout, indices);
    model_manager.bind(model_id);

    const VertexBuffer& vbo = model_manager.getModel(model_id).getVertexBuffer();
    const ElementBuffer& ebo = model_manager.getModel(model_id).getElementBuffer();

    // TODO Buffer Manager needs to pass this data to the GPU. Waiting to start using GL_DYNAMIC_DRAW
    // This could be based on the currently bound buffers. Therefore one would only need to BufferManager::sendDataToGPU(ID)
    glBufferData(GL_ARRAY_BUFFER, vbo.getSize() * sizeof(float), vbo.getData().data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo.getNumberOfBytes(), ebo.getElements().data(), GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex data
    const auto& elements = layout.getElements();

    for (int attributeIndex = 0; attributeIndex < elements.size(); ++attributeIndex) {
        const auto& element = elements[attributeIndex];
        void* offset = 0; // void* due to OpenGL API requiring it

        glVertexAttribPointer(attributeIndex, element.count, element.type, element.normalized, layout.getStride(), offset);
        glEnableVertexAttribArray(attributeIndex);
    }

    // Set up vertex shader
    const std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    // // Set up fragment shader
    const std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        uniform vec4 rectangle_colour;

        void main()
        {
            FragColor = rectangle_colour;
        }
    )";

    Renderex::ShaderManager shader_manager(vertexShaderSource, fragmentShaderSource);

    const unsigned int shader_program_id = shader_manager.getProgramID();

    // Check if this is -1, then it failed to get the uniform location
    const int rectangle_colour_location_ID = glGetUniformLocation(shader_program_id, "rectangle_colour");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float redValue = (std::sin(timeValue) / 2.0f) + 0.5f;
        glUniform4f(rectangle_colour_location_ID, redValue, 1.0f, 0.0f, 1.0f);

        // DearImGUI things
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        std::unique_ptr<bool> showDemoWindow = std::make_unique<bool>(true);
        ImGui::ShowDemoWindow(showDemoWindow.get());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        const int startingIndex = 0;
        const int nVertices = 3;

        const int nIndices = 6;
        const auto ebo_offset = nullptr;
        glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, nullptr);
        // Swaps the front and back buffers of the specified window.
        // The front buffer is the current buffer shown on screen, whilst the back is the data to be drawn to.
        glfwSwapBuffers(window);

        // Poll and process events.
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    std::exit(EXIT_SUCCESS);
}

void APIENTRY GLDebugPrintMessage(GLenum source, GLenum type, unsigned int id, GLenum severity, int length, const char* message, const void* data)
{
    /*

    To enable the debugging layer of OpenGL:

    glEnable(GL_DEBUG_OUTPUT); - This is a faster version but there are no debugger breakpoints.
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); - Callback is synchronized w/ errors, and a breakpoint can be placed on the callback to get a stacktrace for the GL error.

    // Followed by the call:
    glDebugMessageCallback(glDebugPrintMessage, nullptr);
    */

    std::string sourceMessage = "";
    std::string typeMessage = "";
    std::string severityMessage = "";

    switch (source) {
    case GL_DEBUG_SOURCE_API: {
        sourceMessage = "API";
        break;
    }
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: {
        sourceMessage = "WINDOW SYSTEM";
        break;
    }
    case GL_DEBUG_SOURCE_SHADER_COMPILER: {
        sourceMessage = "SHADER COMPILER";
        break;
    }
    case GL_DEBUG_SOURCE_THIRD_PARTY: {
        sourceMessage = "THIRD PARTY";
        break;
    }
    case GL_DEBUG_SOURCE_APPLICATION: {
        sourceMessage = "APPLICATION";
        break;
    }
    case GL_DEBUG_SOURCE_OTHER: {
        sourceMessage = "UNKNOWN";
        break;
    }
    default: {
        sourceMessage = "UNKNOWN";
        break;
    }
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR: {
        typeMessage = "ERROR";
        break;
    }
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: {
        typeMessage = "DEPRECATED BEHAVIOUR";
        break;
    }
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: {
        typeMessage = "UNDEFINED BEHAVIOUR";
        break;
    }
    case GL_DEBUG_TYPE_PORTABILITY: {
        typeMessage = "PORTABILITY";
        break;
    }
    case GL_DEBUG_TYPE_PERFORMANCE: {
        typeMessage = "PERFORMANCE";
        break;
    }
    case GL_DEBUG_TYPE_OTHER: {
        typeMessage = "OTHER";
        break;
    }
    case GL_DEBUG_TYPE_MARKER: {
        typeMessage = "MARKER";
        break;
    }
    default: {
        typeMessage = "UNKNOWN";
        break;
    }
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH: {
        severityMessage = "HIGH";
        break;
    }
    case GL_DEBUG_SEVERITY_MEDIUM: {
        severityMessage = "MEDIUM";
        break;
    }
    case GL_DEBUG_SEVERITY_LOW: {
        severityMessage = "LOW";
        break;
    }
    case GL_DEBUG_SEVERITY_NOTIFICATION: {
        severityMessage = "NOTIFICATION";
        break;
    }
    default: {
        severityMessage = "UNKNOWN";
        break;
    }
    }

    std::cout << id << ": " << typeMessage << " of " << severityMessage << ", raised from "
              << sourceMessage << ": " << message << std::endl;
}
