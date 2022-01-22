#version 330 core

// down :: left right
// up :: left          the opposite triangle will be created based on these coords


layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 6) out;

in vec3 texCoordsGeom[];
in vec4 colorGeom[];
out vec3 texCoordsFrag;
out vec4 colorFrag; // same color all vertices momentarily

void main(void)
{
    int i;

    for (i = 0; i < gl_in.length(); i++)
    {
        texCoordsFrag = texCoordsGeom[i];
        colorFrag = colorGeom[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    // down right
    texCoordsFrag = texCoordsGeom[1];
    colorFrag = colorGeom[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    
    // up left
    texCoordsFrag = texCoordsGeom[2];
    colorFrag = colorGeom[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    
    // up right
    texCoordsFrag = vec3(texCoordsGeom[1].x, texCoordsGeom[2].y, texCoordsGeom[2].z);
    colorFrag = colorGeom[2];
    gl_Position = vec4(gl_in[1].gl_Position.x, gl_in[2].gl_Position.y, 0.0, 1.0);
    EmitVertex();
    EndPrimitive();
}