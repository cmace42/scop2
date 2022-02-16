#include "scop.h"

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
};

t_vao *initOpenGL(t_model model)
{
	t_vao *vao;
	size_t i;

	i = 0;
	if (!(vao = malloc(sizeof(t_vao) * model.size_groupe)))
		return (NULL);
	printf("%zu\n",model.size_groupe);
	while (i < model.size_groupe)
	{
		// see https://youtu.be/hrZbyd4qPnk for VAO et VBO
		glGenVertexArrays(1, &vao[i].VertexArrayID);
		glBindVertexArray(vao[i].VertexArrayID);

		// Ceci identifiera notre tampon de sommets
		// Génère un tampon et place l'identifiant dans 'vertexBuffer'
		printf("Initialisation OpenGL and VAO...\n");
		glGenBuffers(1, &vao[i].vertexBuffer); 
		// Les commandes suivantes vont parler de notre tampon 'vertexBuffer'
		glBindBuffer(GL_ARRAY_BUFFER, vao[i].vertexBuffer); 
		// Fournit les sommets à OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.vertex[i].size_data, model.vertex[i].buffer_data, GL_STATIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		glGenBuffers(1, &vao[i].colorBuffer); 
		glBindBuffer(GL_ARRAY_BUFFER, vao[i].colorBuffer); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.color[i].size_data, model.color[i].buffer_data, GL_STATIC_DRAW);
		glGenBuffers(1, &vao[i].textureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vao[i].textureBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.uv[i].size_data, model.uv[i].buffer_data, GL_STATIC_DRAW);
		i++;
	}
    glGenVertexArrays(1, &vao[0].skyboxVAO);
    glGenBuffers(1, &vao[0].skyboxVBO);
    glBindVertexArray(vao[0].skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, vao[0].skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Active le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// Accepte le fragment s'il est plus proche de la caméra que le précédent accepté
	glDepthFunc(GL_LESS);
	printf("OpenGL and VAO initialised\n");
	return (vao);
}

t_objectInWorld initCamera(t_vec3 whl)
{
	t_objectInWorld camera;
	camera.target = vec3_new(0.0f, 0.0f, 0.0f);
	camera.position = vec3_new(whl.x, whl.y, whl.z * 5 + 10);
	camera.up = vec3_new(0.0f, 1.0f, 5.0f);
	camera.angle.y = 0.0f;
	camera.angle.x = 3.14f;
	return (camera);
}

t_vec3 getWidthHeighLengh(t_bufferData data)
{
	t_vec3 whlMax;
	t_vec3 whlMin;
	size_t i;

	whlMin = (t_vec3){data.buffer_data[0], data.buffer_data[1], data.buffer_data[2]};
	whlMax = (t_vec3){data.buffer_data[0], data.buffer_data[1], data.buffer_data[2]};
	i = 3;
	while (i < data.size_data)
	{
		if (data.buffer_data[i] > whlMax.x)
			whlMax.x = data.buffer_data[i];
		if (data.buffer_data[i + 1] > whlMax.y)
			whlMax.y = data.buffer_data[i + 1];
		if (data.buffer_data[i + 2] > whlMax.z)
			whlMax.z = data.buffer_data[i + 2];
		if (data.buffer_data[i] < whlMin.x)
			whlMin.x = data.buffer_data[i];
		if (data.buffer_data[i + 1] < whlMin.y)
			whlMin.y = data.buffer_data[i + 1];
		if (data.buffer_data[i + 2] < whlMin.z)
			whlMin.z = data.buffer_data[i + 2];
		i += 3;
	}
	return (vec3_add(whlMin, vec3_div_value(vec3_sub(whlMax, whlMin), 2)));
}

t_objectInWorld *initModel(t_model modelData)
{
	t_objectInWorld *model;
	size_t i;

	i = 0;
	if (!(model = malloc(sizeof(t_objectInWorld) * modelData.size_groupe)))
		return NULL;
	while (i < modelData.size_groupe)
	{
		model[i].this = mat4_identity();
		model[i].position = vec3_new(0.0f, 0.0f, 0.0f);
		model[i].target = vec3_new(0.0f, 0.0f, 0.0f);
		model[i].up = vec3_new(0.0f, 1.0f, 5.0f);
		model[i].angle = vec3_new(0.0f, 0.0f, 0.0f);
		model[i].whl = getWidthHeighLengh(modelData.vertex[i]);
		i++;
	}
	return (model);
}