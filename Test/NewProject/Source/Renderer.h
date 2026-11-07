#pragma once

#include <JuceHeader.h>
#include "Model3D.h"

//==============================================================================
/*
    Owns the GL shader program and draws a Model3D with a given camera state.
*/
class Renderer
{
public:
    void initialise (juce::OpenGLContext& context);
    void shutdown();

    void render (juce::OpenGLContext& context, const Model3D& model,
                 int viewportWidth, int viewportHeight,
                 float yaw, float pitch, float distance);

private:
    void createShaders (juce::OpenGLContext& context);

    std::unique_ptr<juce::OpenGLShaderProgram> shader;
    std::unique_ptr<juce::OpenGLShaderProgram::Attribute> position;
    std::unique_ptr<juce::OpenGLShaderProgram::Attribute> sourceColour;
    std::unique_ptr<juce::OpenGLShaderProgram::Uniform> projectionMatrix;
    std::unique_ptr<juce::OpenGLShaderProgram::Uniform> viewMatrix;
};
