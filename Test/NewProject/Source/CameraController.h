#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    Turns mouse drag/scroll input into orbit-camera state (yaw, pitch, distance).
*/
class CameraController
{
public:
    void mouseDown (const juce::MouseEvent& e);
    void mouseDrag (const juce::MouseEvent& e);
    void mouseWheelMove (const juce::MouseWheelDetails& wheel);

    float getYaw() const noexcept      { return yaw; }
    float getPitch() const noexcept    { return pitch; }
    float getDistance() const noexcept { return distance; }

private:
    float yaw = 0.0f, pitch = 0.0f, distance = 10.0f;
    juce::Point<float> lastDragPosition;
};
