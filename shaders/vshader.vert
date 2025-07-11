#version 410 core
in vec2 aPos;
uniform float xTrans;
uniform float yTrans;
void main()
{
    gl_Position = vec4(aPos.x + xTrans, aPos.y + yTrans, 0.0,  1.0);
}
