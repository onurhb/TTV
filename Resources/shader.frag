#version 450 core

in vec4 out_color;
out vec4 frag_color;
in vec4 out_position;


void main()
{
     frag_color = out_position;
}