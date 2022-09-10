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

#include "Setup.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

using namespace ::testing;


TEST(VertexBufferTests, VertexBufferIsGenerated)
{

    Setup::setupBoilerplate();

    std::vector<float> data(0);
    VertexBufferLayout layout;

    VertexBuffer vb("test_vb", data, layout);

    EXPECT_THAT(vb.getID(), Eq(1));
}
