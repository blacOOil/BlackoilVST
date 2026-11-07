#include "CameraController.h"

//==============================================================================
void CameraController::mouseDown (const juce::MouseEvent& e)
{
    lastDragPosition = e.position;
}

void CameraController::mouseDrag (const juce::MouseEvent& e)
{
    auto delta = e.position - lastDragPosition;
    lastDragPosition = e.position;

    const float dragSpeed = 0.01f;
    yaw   += delta.x * dragSpeed;
    pitch += delta.y * dragSpeed;

    pitch = juce::jlimit (-juce::MathConstants<float>::halfPi + 0.01f,
                           juce::MathConstants<float>::halfPi - 0.01f,
                           pitch);
}

void CameraController::mouseWheelMove (const juce::MouseWheelDetails& wheel)
{
    distance = juce::jlimit (3.0f, 50.0f, distance - wheel.deltaY * 5.0f);
}
