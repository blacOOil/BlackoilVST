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
    renderer.initialise (openGLContext);
    model.load();
}

void MainComponent::shutdown()
{
    renderer.shutdown();
    model.release();
}

void MainComponent::render()
{
    renderer.render (openGLContext, model, getWidth(), getHeight(),
                      camera.getYaw(), camera.getPitch(), camera.getDistance());
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
void MainComponent::mouseDown (const juce::MouseEvent& e)
{
    camera.mouseDown (e);
}

void MainComponent::mouseDrag (const juce::MouseEvent& e)
{
    camera.mouseDrag (e);
}

void MainComponent::mouseWheelMove (const juce::MouseEvent&, const juce::MouseWheelDetails& wheel)
{
    camera.mouseWheelMove (wheel);
}
