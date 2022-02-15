#include "scop.h"

// static const GLfloat g_uv_buffer_data[] = { 
// 	0.000059f, 1.0f-0.000004f, 
// 	0.000103f, 1.0f-0.336048f, 
// 	0.335973f, 1.0f-0.335903f, 
// 	1.000023f, 1.0f-0.000013f, 
// 	0.667979f, 1.0f-0.335851f, 
// 	0.999958f, 1.0f-0.336064f, 
// 	0.667979f, 1.0f-0.335851f, 
// 	0.336024f, 1.0f-0.671877f, 
// 	0.667969f, 1.0f-0.671889f, 
// 	1.000023f, 1.0f-0.000013f, 
// 	0.668104f, 1.0f-0.000013f, 
// 	0.667979f, 1.0f-0.335851f, 
// 	0.000059f, 1.0f-0.000004f, 
// 	0.335973f, 1.0f-0.335903f, 
// 	0.336098f, 1.0f-0.000071f, 
// 	0.667979f, 1.0f-0.335851f, 
// 	0.335973f, 1.0f-0.335903f, 
// 	0.336024f, 1.0f-0.671877f, 
// 	1.000004f, 1.0f-0.671847f, 
// 	0.999958f, 1.0f-0.336064f, 
// 	0.667979f, 1.0f-0.335851f, 
// 	0.668104f, 1.0f-0.000013f, 
// 	0.335973f, 1.0f-0.335903f, 
// 	0.667979f, 1.0f-0.335851f, 
// 	0.335973f, 1.0f-0.335903f, 
// 	0.668104f, 1.0f-0.000013f, 
// 	0.336098f, 1.0f-0.000071f, 
// 	0.000103f, 1.0f-0.336048f, 
// 	0.000004f, 1.0f-0.671870f, 
// 	0.336024f, 1.0f-0.671877f, 
// 	0.000103f, 1.0f-0.336048f, 
// 	0.336024f, 1.0f-0.671877f, 
// 	0.335973f, 1.0f-0.335903f, 
// 	0.667969f, 1.0f-0.671889f, 
// 	1.000004f, 1.0f-0.671847f, 
// 	0.667979f, 1.0f-0.335851f 
// };

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
	// Active le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// Accepte le fragment s'il est plus proche de la caméra que le précédent accepté
	glDepthFunc(GL_LESS);
	printf("OpenGL and VAO initialised\n");
	return (vao);
}

bool isPointOnCone(t_vec3 coord, t_vec3 targetCoord, t_vec3 camCoord)
{
	float cone_dist; 
	cone_dist = vec3_dot(vec3_sub(vec3_add_value(camCoord,1),vec3_add_value(coord,1)), vec3_normalisation(vec3_add_value(targetCoord,1)));
	printf("ispointoncone : %f\n",cone_dist);
	if (cone_dist <= 0 || cone_dist >= MAXDIST)
		return (false);
	float cone_radius;
	cone_radius = (cone_dist / MAXDIST) * INITIALFOV;
	float orth_dist;
	// lenght(((coord - camCoord) - (dir * cone_dist)))
	orth_dist = vec3_length
	(
		vec3_sub
		(
			vec3_sub
			(
				vec3_add_value
				(
					coord,
					1
				),
				vec3_add_value
				(
					camCoord,
					1
				)
			),
			vec3_mult_value
			(
				vec3_normalisation
				(
					vec3_add_value
					(
						targetCoord,
						1
					)
				),
				cone_dist
			)
		)
	);
	printf("ispointoncone : %f > %f = %d\n ", orth_dist, cone_radius,orth_dist > cone_radius);
	return (orth_dist > cone_radius);
}

bool isObjectOnCone(t_objectInWorld model, t_vec3 targetCoord, t_vec3 camCoord)
{
	if (!isPointOnCone(model.position, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x,
			.y = model.position.y + model.whl.y,
			.z = model.position.z,
		}, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x + model.whl.x,
			.y = model.position.y,
			.z = model.position.z,
		}, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x + model.whl.x,
			.y = model.position.y + model.whl.y,
			.z = model.position.z,
		}, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x,
			.y = model.position.y,
			.z = model.position.z + model.whl.z,
		}, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x,
			.y = model.position.y + model.whl.y,
			.z = model.position.z + model.whl.z,
		}, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x + model.whl.x,
			.y = model.position.y,
			.z = model.position.z + model.whl.z,
		}, targetCoord, camCoord))
		return (false);
	if (!isPointOnCone((t_vec3) 
		{
			.x = model.position.x + model.whl.x,
			.y = model.position.y + model.whl.y,
			.z = model.position.z + model.whl.z
		}, targetCoord, camCoord))
		return (false);
	return (true);
}

float getZAxis(t_objectInWorld model, t_vec3 targetCoord, t_vec3 camCoord)
{
	int i;

	i = 0;
	printf("yo\n");
	while (!isObjectOnCone(model, targetCoord, camCoord) && i < 200)
	{
		printf("wsh bordel %f\n",camCoord.z);
		camCoord.z += vec3_length(vec3_sub(model.position, camCoord));
		i++;
	}
	return camCoord.z;
}

t_objectInWorld initCamera()
{
	t_objectInWorld camera;
	camera.target = vec3_new(0.0f, 0.0f, 0.0f);
	camera.position = vec3_new(0.0f, 0.0f, 10.0f);
	// camera.position = vec3_new(0.0f, 0.0f, getZAxis(model, camera.target, (t_vec3){0.0f, 0.0f, 0.1f}));
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