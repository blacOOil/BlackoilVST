#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    Holds the vertex/index data for a 3D mesh and owns its GL buffers.
*/
class Model3D
{
public:
    struct Vertex
    {
        float position[3];
        float colour[4];
    };

    void load();
    void release();

    void bind() const;
    void unbind() const;

    int getNumIndices() const noexcept { return (int) indices.size(); }

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLuint vertexBuffer = 0, indexBuffer = 0;
};
