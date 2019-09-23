#version 330 core

in vec2 fs_texCoords;

out vec4 FragColor;

uniform sampler2D u_textureSampler;

void main(){
	FragColor = texture(u_textureSampler, fs_texCoords);
}