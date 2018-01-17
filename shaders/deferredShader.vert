#version 330

layout(location = 0) in vec3 vertexIn;
layout(location = 1) in vec2 textureCoordinateIn;
out vec2 textureCoordinateOut; // Passthrough

void main(){

	textureCoordinateOut = textureCoordinateIn; //Passthrough
	gl_Position = vec4(vertexIn.xyz, 1.0); //Passthrough
}