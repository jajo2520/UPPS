#version 410 core
in vec2 aPos;
uniform vec2 pos;
uniform vec2 screenSize;
void main()
{
    vec2 currentPos = aPos;
    currentPos += pos;
    vec2 clipSpace = (currentPos / screenSize) * 2.0 - 1.0; 
    gl_Position = vec4(clipSpace, 0.0, 1.0); 
}
