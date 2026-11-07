#include "Renderer.h"

//==============================================================================
void Renderer::initialise (juce::OpenGLContext& context)
{
    createShaders (context);
}

void Renderer::shutdown()
{
    shader.reset();
    position.reset();
    sourceColour.reset();
    projectionMatrix.reset();
    viewMatrix.reset();
}

void Renderer::render (juce::OpenGLContext& context, const Model3D& model,
                        int viewportWidth, int viewportHeight,
                        float yaw, float pitch, float distance)
{
    juce::OpenGLHelpers::clear (juce::Colour::fromFloatRGBA (0.08f, 0.08f, 0.1f, 1.0f));

    auto desktopScale = (float) context.getRenderingScale();
    juce::gl::glViewport (0, 0,
                           juce::roundToInt (desktopScale * (float) viewportWidth),
                           juce::roundToInt (desktopScale * (float) viewportHeight));

    juce::gl::glEnable (juce::gl::GL_DEPTH_TEST);
    juce::gl::glDepthFunc (juce::gl::GL_LESS);

    if (shader == nullptr)
        return;

    shader->use();

    if (projectionMatrix != nullptr)
    {
        auto w = 1.0f / (viewportWidth > 0 ? (float) viewportWidth / (float) viewportHeight : 1.0f);
        juce::Matrix3D<float> proj (juce::Matrix3D<float>::fromFrustum (-w, w, -1.0f, 1.0f, 4.0f, 30.0f));
        projectionMatrix->setMatrix4 (proj.mat, 1, false);
    }

    if (viewMatrix != nullptr)
    {
        juce::Matrix3D<float> rotationMatrix = juce::Matrix3D<float>::rotation ({ pitch, yaw, 0.0f });
        juce::Matrix3D<float> translationMatrix = juce::Matrix3D<float>::fromTranslation ({ 0.0f, 0.0f, -distance });
        juce::Matrix3D<float> viewMat = translationMatrix * rotationMatrix;
        viewMatrix->setMatrix4 (viewMat.mat, 1, false);
    }

    model.bind();

    if (position != nullptr)
    {
        juce::OpenGLExtensionFunctions::glVertexAttribPointer (
            (GLuint) position->attributeID, 3, juce::gl::GL_FLOAT, juce::gl::GL_FALSE,
            sizeof (Model3D::Vertex), (GLvoid*) offsetof (Model3D::Vertex, position));
        juce::OpenGLExtensionFunctions::glEnableVertexAttribArray ((GLuint) position->attributeID);
    }

    if (sourceColour != nullptr)
    {
        juce::OpenGLExtensionFunctions::glVertexAttribPointer (
            (GLuint) sourceColour->attributeID, 4, juce::gl::GL_FLOAT, juce::gl::GL_FALSE,
            sizeof (Model3D::Vertex), (GLvoid*) offsetof (Model3D::Vertex, colour));
        juce::OpenGLExtensionFunctions::glEnableVertexAttribArray ((GLuint) sourceColour->attributeID);
    }

    juce::gl::glDrawElements (juce::gl::GL_TRIANGLES, model.getNumIndices(), juce::gl::GL_UNSIGNED_INT, nullptr);

    if (position != nullptr)
        juce::OpenGLExtensionFunctions::glDisableVertexAttribArray ((GLuint) position->attributeID);

    if (sourceColour != nullptr)
        juce::OpenGLExtensionFunctions::glDisableVertexAttribArray ((GLuint) sourceColour->attributeID);

    model.unbind();
}

//==============================================================================
void Renderer::createShaders (juce::OpenGLContext& context)
{
    auto vertexShader   = juce::String::fromUTF8 (BinaryData::Basic_vert, BinaryData::Basic_vertSize);
    auto fragmentShader = juce::String::fromUTF8 (BinaryData::Basic_frag, BinaryData::Basic_fragSize);

    std::unique_ptr<juce::OpenGLShaderProgram> newShader (new juce::OpenGLShaderProgram (context));

    if (newShader->addVertexShader (juce::OpenGLHelpers::translateVertexShaderToV3 (vertexShader))
        && newShader->addFragmentShader (juce::OpenGLHelpers::translateFragmentShaderToV3 (fragmentShader))
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
