#version 410 core
out vec4 fragColor;
uniform vec2 vel;

void main()
{
    float maxVelCol = 350.f;
    float scaleFac = 25.f;
    float velMag = length(vel);
    float red = 1 / (1 + exp(-(1/scaleFac)*(velMag - maxVelCol/2)));
    float blue = 1 / (1 + exp(-(1/scaleFac)*(maxVelCol/2 - velMag)));
    fragColor = vec4(red, 0, blue, 1.0);
}
