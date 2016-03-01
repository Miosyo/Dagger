#version 330

attribute vec2 position;

void main()
{
    // Transforming The Vertex
    gl_Position = vec4(position, 0.0, 1.0);
}