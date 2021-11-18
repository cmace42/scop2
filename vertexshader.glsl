#version 330 core

layout(location = 0) in vec3 vertexPostion_modelSpace;
// Notez que le "1" ici correspond au "1" dans glVertexAttribPointer 
layout(location = 1) in vec3 vertexColor;
// Données de sortie ; sera interpolée pour chaque fragment
out vec3 fragmentColor;

void main(){
	gl_Position.xyz = vertexPostion_modelSpace;
	gl_Position.w = 1.0;
	fragmentColor = vertexColor;
}