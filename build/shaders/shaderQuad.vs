#version 330 core

layout (location = 0) in vec2 in_vertices;
layout (location = 1) in vec2 in_texCoords;

out vec2 fs_texCoords;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;


void main(){
	vec4 position = vec4(in_vertices.x,in_vertices.y,0.0,1.0);
	mat4 mvp_matrix =  u_projection*u_view  * u_model;
	gl_Position = mvp_matrix * position;
	fs_texCoords = in_texCoords;
}