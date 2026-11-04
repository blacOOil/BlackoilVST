#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
}

MainComponent::~MainComponent()
{
    // This shuts down the GL system and stops the rendering calls.
    shutdownOpenGL();
}

//==============================================================================
void MainComponent::initialise()
{
    createShaders();

    // Cube vertices (position + colour per face corner, flat-shaded via per-vertex colour)
    const Vertex vertices[] =
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

    const GLuint indices[] =
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
    juce::OpenGLExtensionFunctions::glBufferData (juce::gl::GL_ARRAY_BUFFER, sizeof (vertices), vertices, juce::gl::GL_STATIC_DRAW);

    juce::OpenGLExtensionFunctions::glGenBuffers (1, &indexBuffer);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    juce::OpenGLExtensionFunctions::glBufferData (juce::gl::GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, juce::gl::GL_STATIC_DRAW);
}

void MainComponent::shutdown()
{
    shader.reset();
    position.reset();
    sourceColour.reset();
    projectionMatrix.reset();
    viewMatrix.reset();

    if (vertexBuffer != 0)
        juce::OpenGLExtensionFunctions::glDeleteBuffers (1, &vertexBuffer);

    if (indexBuffer != 0)
        juce::OpenGLExtensionFunctions::glDeleteBuffers (1, &indexBuffer);
}

void MainComponent::render()
{
    juce::OpenGLHelpers::clear (juce::Colour::fromFloatRGBA (0.08f, 0.08f, 0.1f, 1.0f));

    auto desktopScale = (float) openGLContext.getRenderingScale();
    juce::gl::glViewport (0, 0,
                           juce::roundToInt (desktopScale * (float) getWidth()),
                           juce::roundToInt (desktopScale * (float) getHeight()));

    juce::gl::glEnable (juce::gl::GL_DEPTH_TEST);
    juce::gl::glDepthFunc (juce::gl::GL_LESS);

    shader->use();

    if (projectionMatrix != nullptr)
    {
        auto w = 1.0f / (getWidth() > 0 ? (float) getWidth() / (float) getHeight() : 1.0f);
        juce::Matrix3D<float> proj (juce::Matrix3D<float>::fromFrustum (-w, w, -1.0f, 1.0f, 4.0f, 30.0f));
        projectionMatrix->setMatrix4 (proj.mat, 1, false);
    }

    if (viewMatrix != nullptr)
    {
        rotation += 0.01f;

        juce::Matrix3D<float> rotationMatrix = juce::Matrix3D<float>::rotation ({ rotation * 0.7f, rotation, rotation * 0.4f });
        juce::Matrix3D<float> translationMatrix = juce::Matrix3D<float>::fromTranslation ({ 0.0f, 0.0f, -10.0f });
        juce::Matrix3D<float> viewMat = translationMatrix * rotationMatrix;
        viewMatrix->setMatrix4 (viewMat.mat, 1, false);
    }

    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ARRAY_BUFFER, vertexBuffer);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    if (position != nullptr)
    {
        juce::OpenGLExtensionFunctions::glVertexAttribPointer (
            (GLuint) position->attributeID, 3, juce::gl::GL_FLOAT, juce::gl::GL_FALSE,
            sizeof (Vertex), (GLvoid*) offsetof (Vertex, position));
        juce::OpenGLExtensionFunctions::glEnableVertexAttribArray ((GLuint) position->attributeID);
    }

    if (sourceColour != nullptr)
    {
        juce::OpenGLExtensionFunctions::glVertexAttribPointer (
            (GLuint) sourceColour->attributeID, 4, juce::gl::GL_FLOAT, juce::gl::GL_FALSE,
            sizeof (Vertex), (GLvoid*) offsetof (Vertex, colour));
        juce::OpenGLExtensionFunctions::glEnableVertexAttribArray ((GLuint) sourceColour->attributeID);
    }

    juce::gl::glDrawElements (juce::gl::GL_TRIANGLES, 36, juce::gl::GL_UNSIGNED_INT, nullptr);

    if (position != nullptr)
        juce::OpenGLExtensionFunctions::glDisableVertexAttribArray ((GLuint) position->attributeID);

    if (sourceColour != nullptr)
        juce::OpenGLExtensionFunctions::glDisableVertexAttribArray ((GLuint) sourceColour->attributeID);

    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ARRAY_BUFFER, 0);
    juce::OpenGLExtensionFunctions::glBindBuffer (juce::gl::GL_ELEMENT_ARRAY_BUFFER, 0);
}

//==============================================================================
void MainComponent::paint (juce::Graphics&)
{
    // Rendering happens entirely in the OpenGL render() callback.
}

void MainComponent::resized()
{
}

//==============================================================================
void MainComponent::createShaders()
{
    newVertexShader =
        "attribute vec4 position;\n"
        "attribute vec4 sourceColour;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "varying vec4 destinationColour;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    destinationColour = sourceColour;\n"
        "    gl_Position = projectionMatrix * viewMatrix * position;\n"
        "}\n";

    newFragmentShader =
        "varying vec4 destinationColour;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = destinationColour;\n"
        "}\n";

    std::unique_ptr<juce::OpenGLShaderProgram> newShader (new juce::OpenGLShaderProgram (openGLContext));

    if (newShader->addVertexShader (juce::OpenGLHelpers::translateVertexShaderToV3 (newVertexShader))
        && newShader->addFragmentShader (juce::OpenGLHelpers::translateFragmentShaderToV3 (newFragmentShader))
        && newShader->link())
    {
        shader.reset (newShader.release());
        shader->use();

        position.reset (new juce::OpenGLShaderProgram::Attribute (*shader, "position"));
        sourceColour.reset (new juce::OpenGLShaderProgram::Attribute (*shader, "sourceColour"));
        projectionMatrix.reset (new juce::OpenGLShaderProgram::Uniform (*shader, "projectionMatrix"));
        viewMatrix.reset (new juce::OpenGLShaderProgram::Uniform (*shader, "viewMatrix"));
    }
}
