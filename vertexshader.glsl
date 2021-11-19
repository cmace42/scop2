#version 330 core

layout(location = 0) in vec3 vertexPostion_modelSpace;
// Notez que le "1" ici correspond au "1" dans glVertexAttribPointer 
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexPostion_modelSpace2;
// Notez que le "1" ici correspond au "1" dans glVertexAttribPointer 
layout(location = 3) in vec3 vertexColor2;
// Données de sortie ; sera interpolée pour chaque fragment
out vec3 fragmentColor;
uniform mat4 MVP; 
uniform mat4 MVP2; 

void main(){
	vec4 v = vec4(vertexPostion_modelSpace, 1); // Transforme un vecteur 4D homogène
	vec4 v2 = vec4(vertexPostion_modelSpace2, 1); // Transforme un vecteur 4D homogène
	gl_Position = MVP * v;
	fragmentColor = vertexColor;
}