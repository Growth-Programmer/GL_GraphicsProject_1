#version 430
uniform float offset;
void main(void)
{
    if (gl_VertexID == 0)
        gl_Position = vec4(0.15 + offset,-0.05,0.0,1.0);
    else if (gl_VertexID == 1)
        gl_Position = vec4(-0.05 + offset,-0.05,0.0,1.0);
    else
        gl_Position = vec4(0.05 + offset,0.05,0.0,1.0);
}