#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D ourTexture;
uniform vec4 color;

void main()
{
  FragColor =  texture2D(ourTexture, TexCoords) * color;
//  FragColor =  color;
}