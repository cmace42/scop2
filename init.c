#include "scop.h"

static const GLfloat g_vertex_buffer_data[] = { 
    -1.0f,-1.0f,-1.0f, // triangle 1 : début
    -1.0f,-1.0f, 1.0f, 
    -1.0f, 1.0f, 1.0f, // triangle 1 : fin 
    1.0f, 1.0f,-1.0f, // triangle 2 : début 
    -1.0f,-1.0f,-1.0f, 
    -1.0f, 1.0f,-1.0f, // triangle 2 : fin 
    1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f,-1.0f, 
    1.0f,-1.0f,-1.0f, 
    1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f, 
    -1.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f,-1.0f, 
    -1.0f, 1.0f, 1.0f, 
    -1.0f,-1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f,-1.0f, 
    1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f,-1.0f, 
    1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 
    1.0f, 1.0f,-1.0f, 
    -1.0f, 1.0f,-1.0f, 
    1.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f,-1.0f, 
    -1.0f, 1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f 
};

static const GLfloat g_uv_buffer_data[] = { 
    0.000059f, 1.0f-0.000004f, 
    0.000103f, 1.0f-0.336048f, 
    0.335973f, 1.0f-0.335903f, 
    1.000023f, 1.0f-0.000013f, 
    0.667979f, 1.0f-0.335851f, 
    0.999958f, 1.0f-0.336064f, 
    0.667979f, 1.0f-0.335851f, 
    0.336024f, 1.0f-0.671877f, 
    0.667969f, 1.0f-0.671889f, 
    1.000023f, 1.0f-0.000013f, 
    0.668104f, 1.0f-0.000013f, 
    0.667979f, 1.0f-0.335851f, 
    0.000059f, 1.0f-0.000004f, 
    0.335973f, 1.0f-0.335903f, 
    0.336098f, 1.0f-0.000071f, 
    0.667979f, 1.0f-0.335851f, 
    0.335973f, 1.0f-0.335903f, 
    0.336024f, 1.0f-0.671877f, 
    1.000004f, 1.0f-0.671847f, 
    0.999958f, 1.0f-0.336064f, 
    0.667979f, 1.0f-0.335851f, 
    0.668104f, 1.0f-0.000013f, 
    0.335973f, 1.0f-0.335903f, 
    0.667979f, 1.0f-0.335851f, 
    0.335973f, 1.0f-0.335903f, 
    0.668104f, 1.0f-0.000013f, 
    0.336098f, 1.0f-0.000071f, 
    0.000103f, 1.0f-0.336048f, 
    0.000004f, 1.0f-0.671870f, 
    0.336024f, 1.0f-0.671877f, 
    0.000103f, 1.0f-0.336048f, 
    0.336024f, 1.0f-0.671877f, 
    0.335973f, 1.0f-0.335903f, 
    0.667969f, 1.0f-0.671889f, 
    1.000004f, 1.0f-0.671847f, 
    0.667979f, 1.0f-0.335851f 
};

t_vao initOpenGL()
{
	t_vao vao;
	// see https://youtu.be/hrZbyd4qPnk for VAO et VBO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Ceci identifiera notre tampon de sommets
	// Génère un tampon et place l'identifiant dans 'vertexBuffer'
	glGenBuffers(1, &vao.vertexBuffer); 
	// Les commandes suivantes vont parler de notre tampon 'vertexBuffer'
	glBindBuffer(GL_ARRAY_BUFFER, vao.vertexBuffer); 
	// Fournit les sommets à OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &vao.textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vao.textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    // Active le test de profondeur
    glEnable(GL_DEPTH_TEST); 
    // Accepte le fragment s'il est plus proche de la caméra que le précédent accepté
    glDepthFunc(GL_LESS);
	return (vao);
}