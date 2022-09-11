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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "ElementBuffer.h"
#include "Setup.h"

#include <string>

using namespace ::testing;

TEST(ElementBufferTests, ElementBufferIsGenerated)
{

    Setup::setupBoilerplate();

    const std::vector<unsigned int> data(0);
    const std::string name = "test_element_buffer";
    const ElementBuffer eb(name, data);

    EXPECT_THAT(eb.getID(), Eq(1));
}
