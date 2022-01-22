#version 330 core
out vec4 FragColor;

in vec3 texCoordsFrag;
in vec4 colorFrag;

uniform sampler2DArray TextureArray;

void main()
{
    float red = texture(TextureArray, texCoordsFrag).r;

      //FragColor = vec4(1,1,1,texture(ourTexture, vec3(texCoordsFrag.xy, 5)).r);
     // FragColor = vec4(texture(ourTexture, vec3(texCoordsFrag.xy, 10)).xyz, 1);
   // if(red == 0)
    //   FragColor = vec4(0,0,0,1);
    //else
        FragColor = vec4(1,1,1, red) * colorFrag;
   
}