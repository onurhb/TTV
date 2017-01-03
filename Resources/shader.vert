#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec4 out_color;
out vec4 out_position;

void main()
{
     gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
     out_position = pr_matrix * vw_matrix * ml_matrix * position;
     out_color =  color;
}