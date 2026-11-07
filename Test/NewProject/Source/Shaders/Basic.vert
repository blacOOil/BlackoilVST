attribute vec4 position;
attribute vec4 sourceColour;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
varying vec4 destinationColour;

void main()
{
    destinationColour = sourceColour;
    gl_Position = projectionMatrix * viewMatrix * position;
}
