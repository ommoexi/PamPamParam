#version 330 core
out vec4 FragColor;

in vec3 texCoordsFrag;
in vec4 colorFrag;

uniform sampler2DArray TextureArray;

void main()
{

    FragColor = texture(TextureArray, texCoordsFrag) * colorFrag;
   
}