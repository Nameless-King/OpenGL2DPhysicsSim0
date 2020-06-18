#version 330 core

in vec2 fs_texCoords;

out vec4 FragColor;

uniform sampler2D u_textureSampler;

void main(){
	FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
	//FragColor = texture(u_textureSampler, fs_texCoords);
}
