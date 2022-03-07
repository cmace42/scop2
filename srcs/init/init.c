/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:10:00 by cmace             #+#    #+#             */
/*   Updated: 2022/03/07 17:20:14 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

extern char	vertexshader_glsl[];
extern int	vertexshader_glsl_len;
extern char	fragmentshader_glsl[];
extern int	fragmentshader_glsl_len;

t_vao	*initOpenGL(t_model model)
{
	t_vao	*vao;
	size_t	i;

	i = 0;
	if (!(vao = malloc(sizeof(t_vao) * model.size_groupe)))
		return (NULL);
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
		glGenBuffers(1, &vao[i].colorTrianglesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vao[i].colorTrianglesBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.colorTriangles[i].size_data, model.colorTriangles[i].buffer_data, GL_STATIC_DRAW);
		glGenBuffers(1, &vao[i].colorFacesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vao[i].colorFacesBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.colorFaces[i].size_data, model.colorFaces[i].buffer_data, GL_STATIC_DRAW);
		glGenBuffers(1, &vao[i].textureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vao[i].textureBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.uv[i].size_data, model.uv[i].buffer_data, GL_STATIC_DRAW);
		i++;
	}
	// Active le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// Accepte le fragment s'il est plus proche de la caméra que le précédent accepté
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	printf("OpenGL and VAO initialised\n");
	return (vao);
}

t_objectInWorld	initCamera(t_vec3 whl)
{
	t_objectInWorld	camera;
	camera.target = vec3_new(0.0f, 0.0f, 0.0f);
	camera.position = vec3_new(whl.x, whl.y, whl.z * 5 + 10);
	camera.up = vec3_new(0.0f, 1.0f, 5.0f);
	camera.angle.y = 0.0f;
	camera.angle.x = 3.14f;
	return (camera);
}

t_vec3	getWidthHeighLengh(t_bufferData data)
{
	t_vec3	whlMax;
	t_vec3	whlMin;
	size_t	i;

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

t_objectInWorld	*initModel(t_model modelData)
{
	t_objectInWorld	*model;
	size_t			i;

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

t_action	initAction(void)
{
	t_action	action;

	action.showTexture = false;
	action.autoColor = false;
	action.transition = 1;
	action.rotate = true;
	action.rotateKeyboardMode = true;
	action.isBmp1 = false;
	action.haveSpeedBoost = false;
	action.showFace = 1;
	action.showDept = false;
	action.greymode = true;
	action.glcullface = false;
	action.colorInc = (t_vec3){0.0000f, 0.0000f, 0.0000f};
	action.colorBackMode = false;
	action.speedColor = 1.5f;
	return (action);
}

int				init(t_env *env, char *filename, char *textureFilename)
{
	int	ret;

	if ((ret = getModel(filename, &env->modelData)) == GET_RESULT)
	{
		if ((env->window = initWindow()) != NULL)
		{
			SDL_SetRelativeMouseMode(true);
			env->context = SDL_GL_CreateContext(env->window);
			if (!(env->vao = initOpenGL(env->modelData)))
				return (FAILEDTOINITVAO);
			if (!(env->model = initModel(env->modelData)))
			{
				printf("merde\n");
				return (FAILEDTOINITMODEL);
			}
			env->camera = initCamera(initAllWhl(env->model, env->modelData.size_groupe));
			if (loadBMP_custom("./ressources/textures/petit-poney.bmp", &env->bmp[0]) != GET_RESULT)
				return (FAILEDTOINITBMP);
			if (loadBMP_custom(textureFilename != NULL ? textureFilename : "./ressources/textures/texturetest.bmp", &env->bmp[1]) != GET_RESULT)
				return (FAILEDTOINITBMP);
			env->programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
			env->texture = getTextureId(env->bmp[1]);
			env->action = initAction();
			env->time.lastTime = 0;
			env->speed = fabs(env->model[0].whl.y) / 20.0f;
		}
		else
		{
			printf("Failed to init window\n");
			return (FAILEDTOINITWINDOW);
		}
	}
	return (ret);
}
