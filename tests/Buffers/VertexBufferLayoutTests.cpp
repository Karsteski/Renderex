#include "VertexBufferLayout.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <GL/glew.h>

using namespace ::testing;

TEST(VertexBufferLayout, CorrectStrideIsCalculated)
{
    VertexBufferLayout layout;
    const int nIntsForPositionAttribute = 3;
    layout.push<unsigned int>("int", nIntsForPositionAttribute); // 12 bytes
    const float nFloatsForColourAttribute = 4;
    layout.push<float>("colour", nFloatsForColourAttribute); // 16 bytes
    const char nUnsignedCharsForMiscAttribute = 1;
    layout.push<unsigned char>("miscellaneous", nUnsignedCharsForMiscAttribute); // 1 byte

    // Stride is the distance between vertices.
    // Therefore the stride between vertices should be 12 + 16 = 28
    const int stride = (nIntsForPositionAttribute * sizeof(float))
        + (nFloatsForColourAttribute * sizeof(float))
        + (nUnsignedCharsForMiscAttribute * sizeof(unsigned char));

    EXPECT_THAT(layout.getStride(), Eq(stride));
}

TEST(VertexBufferLayout, LayoutIsSetupCorrectly)
{
    VertexBufferLayout layout;

    const int nIntsForPositionAttribute = 3;
    const std::string position = "position";
    layout.push<unsigned int>(position, nIntsForPositionAttribute);

    const int nFloatsForColourAttribute = 4;
    const std::string colour = "colour";
    layout.push<float>(colour, nFloatsForColourAttribute);

    const char nUnsignedCharsForMiscAttribute = 1;
    const std::string miscellaneous = "miscellaneous";
    layout.push<unsigned char>(miscellaneous, nUnsignedCharsForMiscAttribute);

    const auto elements = layout.getElements();

    EXPECT_THAT(elements[0].name, Eq(position));
    EXPECT_THAT(elements[0].count, Eq(nIntsForPositionAttribute));
    EXPECT_THAT(elements[0].type, Eq(GL_UNSIGNED_INT));

    EXPECT_THAT(elements[1].name, Eq(colour));
    EXPECT_THAT(elements[1].count, Eq(nFloatsForColourAttribute));
    EXPECT_THAT(elements[1].type, Eq(GL_FLOAT));

    EXPECT_THAT(elements[2].name, Eq(miscellaneous));
    EXPECT_THAT(elements[2].count, Eq(nUnsignedCharsForMiscAttribute));
    EXPECT_THAT(elements[2].type, Eq(GL_UNSIGNED_BYTE));
}
