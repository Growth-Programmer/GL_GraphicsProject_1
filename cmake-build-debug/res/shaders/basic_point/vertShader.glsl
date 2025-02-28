#version 430
uniform float offset;
uniform float size;

void main(void)
{
    if (gl_VertexID == 0)
        gl_Position = vec4((0.15 + offset) * size, -0.05 * size, 0.0 * size, 1.0);
    else if (gl_VertexID == 1)
        gl_Position = vec4((-0.05 + offset) * size, -0.05 * size, 0.0 * size, 1.0);
    else
        gl_Position = vec4((0.05 + offset) * size, 0.15 * size, 0.0 * size, 1.0);
}