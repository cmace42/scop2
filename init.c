#include "scop.h"

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

t_vao initOpenGL(t_model model)
{
	t_vao vao;
	// see https://youtu.be/hrZbyd4qPnk for VAO et VBO
	glGenVertexArrays(1, &vao.VertexArrayID);
	glBindVertexArray(vao.VertexArrayID);

	// Ceci identifiera notre tampon de sommets
	// Génère un tampon et place l'identifiant dans 'vertexBuffer'
	printf("start init vertexbufferdata\n");
	glGenBuffers(1, &vao.vertexBuffer); 
	// Les commandes suivantes vont parler de notre tampon 'vertexBuffer'
	glBindBuffer(GL_ARRAY_BUFFER, vao.vertexBuffer); 
	// Fournit les sommets à OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.vertex_size_data * 3, model.vertex_buffer_data, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	printf("end init vertexbufferdata\n");
	printf("start init colorbufferdata\n");
	glGenBuffers(1, &vao.colorBuffer); 
	glBindBuffer(GL_ARRAY_BUFFER, vao.colorBuffer); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.vertex_size_data * 3, model.vertex_buffer_data, GL_STATIC_DRAW);
	printf("end init colorbufferdata\n");
	glGenBuffers(1, &vao.textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vao.textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.uv_static_size_data, model.uv_static_buffer_data, GL_STATIC_DRAW);
	printf("end init texturebufferdata\n");
	// Active le test de profondeur
	glEnable(GL_DEPTH_TEST); 
	// Accepte le fragment s'il est plus proche de la caméra que le précédent accepté
	glDepthFunc(GL_LESS);
	return (vao);
}

t_objectInWorld initCamera()
{
	t_objectInWorld camera;
	camera.position = vec3_new(0.0f, 0.0f, 10.0f);
	camera.target = vec3_new(0.0f, 0.0f, 0.0f);
	camera.up = vec3_new(0.0f, 1.0f, 5.0f);
	camera.angle.y = 0.0f;
	camera.angle.x = 3.14f;
	return (camera);
}

t_objectInWorld initModel(t_vec3 whl)
{
	t_objectInWorld model;
	model.mod = mat4_identity();
	model.position = vec3_new(0.0f, 0.0f, 0.0f);
	model.target = vec3_new(0.0f, 0.0f, 0.0f);
	model.up = vec3_new(0.0f, 1.0f, 5.0f);
	model.angle.x = 0;
	model.angle.y = 0;
	model.angle.z = 0;
	model.whl = whl;
	return (model);
}