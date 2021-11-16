#version 330 core

layout(location = 0) in vec3 vertexPostion_modelSpace;

void main(){
	gl_Position.xyz = vertexPostion_modelSpace;
	gl_Position.w = 1.0;
}