#version 410 core

in vec4 vert;
in vec2 vertTexCoord;

out vec2 fragTexCoord;

uniform mat4 proj;

void main()
{
   // Pass the tex coord straight through to the fragment shader
   fragTexCoord = vertTexCoord;
   gl_Position = proj*vert;
}
