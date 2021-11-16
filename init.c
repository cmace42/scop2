#include "scop.h"

static const GLfloat g_vertex_buffer_data[] = { 
   -1.0f, -1.0f, 0.0f, 
   1.0f, -1.0f, 0.0f, 
   0.0f,  1.0f, 0.0f, 
};

GLuint initOpenGL()
{
	// see https://youtu.be/hrZbyd4qPnk for VAO et VBO
	GLuint VertexArrayID; 
	glGenVertexArrays(1, &VertexArrayID); 
	glBindVertexArray(VertexArrayID);
	// Ceci identifiera notre tampon de sommets
	GLuint vertexBuffer; 
 
	// Génère un tampon et place l'identifiant dans 'vertexBuffer'
	glGenBuffers(1, &vertexBuffer); 
 
	// Les commandes suivantes vont parler de notre tampon 'vertexBuffer'
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); 
 
	// Fournit les sommets à OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}