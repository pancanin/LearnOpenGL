#version 330 core
out vec4 FragColor;

in vec4 positionColor;

void main()
{
    FragColor = positionColor;
}