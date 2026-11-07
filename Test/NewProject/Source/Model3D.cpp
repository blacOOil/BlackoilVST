#include "Model3D.h"

//==============================================================================
void Model3D::load()
{
    vertices =
    {
        // front (red)
        { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.2f, 0.2f, 1.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.2f, 0.2f, 1.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.2f, 0.2f, 1.0f } },
        { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.2f, 0.2f, 1.0f } },
        // back (green)
        { { -0.5f, -0.5f, -0.5f }, { 0.2f, 1.0f, 0.2f, 1.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.2f, 1.0f, 0.2f, 1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.2f, 1.0f, 0.2f, 1.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.2f, 1.0f, 0.2f, 1.0f } },
    };

    indices =
    {
        0, 1, 2,  2, 3, 0,   // front
        1, 5, 6,  6, 2, 1,   // right
        5, 4, 7,  7, 6, 5,   // back
        4, 0, 3,  3, 7, 4,   // left
        3, 2, 6,  6, 7, 3,   // top
        4, 5, 1,  1, 0, 4,   // bottom
    };

    juce::OpenGLExtensionFunctions::glGenBuffers (1, &vertexBuffer);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ARRAY_BUFFER, vertexBuffer);
    juce::OpenGLExtensionFunctions::glBufferData (juce::gl::GL_ARRAY_BUFFER,
                                                   (GLsizeiptr) (vertices.size() * sizeof (Vertex)),
                                                   vertices.data(), juce::gl::GL_STATIC_DRAW);

    juce::OpenGLExtensionFunctions::glGenBuffers (1, &indexBuffer);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    juce::OpenGLExtensionFunctions::glBufferData (juce::gl::GL_ELEMENT_ARRAY_BUFFER,
                                                   (GLsizeiptr) (indices.size() * sizeof (GLuint)),
                                                   indices.data(), juce::gl::GL_STATIC_DRAW);
}

void Model3D::release()
{
    if (vertexBuffer != 0)
    {
        juce::OpenGLExtensionFunctions::glDeleteBuffers (1, &vertexBuffer);
        vertexBuffer = 0;
    }

    if (indexBuffer != 0)
    {
        juce::OpenGLExtensionFunctions::glDeleteBuffers (1, &indexBuffer);
        indexBuffer = 0;
    }

    vertices.clear();
    indices.clear();
}

void Model3D::bind() const
{
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ARRAY_BUFFER, vertexBuffer);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

void Model3D::unbind() const
{
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ARRAY_BUFFER, 0);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ELEMENT_ARRAY_BUFFER, 0);
}
