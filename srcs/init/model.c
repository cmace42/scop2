/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:22 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 16:43:33 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/scop.h"

static const t_vec3	color[] = {
	(t_vec3){2, 57, 74},
	(t_vec3){4.0f, 53.0f, 101.0f},
	(t_vec3){81.0f, 88.0f, 187.0f},
	(t_vec3){235.0f, 75.0f, 152.0f},
	(t_vec3){255.0f, 136.0f, 17.0f},
	(t_vec3){244.0f, 208.0f, 111.0f},
	(t_vec3){255.0f, 248.0f, 240.0f},
	(t_vec3){57.0f, 47.0f, 90.0f},
	(t_vec3){30.0f, 0.0f, 14.0f},
	(t_vec3){130.0f, 48.0f, 56.0f},
	(t_vec3){222.0f, 196.0f, 111.0f},
	(t_vec3){244.0f, 247.0f, 190.0f},
	(t_vec3){31.0f, 101.0f, 138.0f},
	(t_vec3){134.0f, 187.0f, 2016.0f},
	(t_vec3){117.0f, 142.0f, 79.0f},
	(t_vec3){246.0f, 174.0f, 45.0f},
	(t_vec3){242.0f, 100.0f, 25.0f},
	(t_vec3){114.0f, 189.0f, 163.0f},
	(t_vec3){148.0f, 232.0f, 180.0f},
	(t_vec3){8.0f, 23.0f, 180.0f},
};

bool	initBuffer(t_obj obj, t_model *model)
{
	size_t	iGroupe;
	size_t	z;

	iGroupe = 0;
	z = 0;
	if (obj.len > 1)
	{
		iGroupe = 1;
		model->size_groupe = obj.len - 1;
	}
	else
		model->size_groupe = obj.len;
	if (!(model->vertex = malloc(sizeof(t_bufferData) * model->size_groupe)))
		return (false);
	if (!(model->uv = malloc(sizeof(t_bufferData) * model->size_groupe)))
		return (false);
	if (!(model->normal = malloc(sizeof(t_bufferData) * model->size_groupe)))
		return (false);
	if (!(model->colorTriangles = malloc(sizeof(t_bufferData) * model->size_groupe)))
		return (false);
	if (!(model->colorFaces = malloc(sizeof(t_bufferData) * model->size_groupe)))
		return (false);
	while (iGroupe < obj.len)
	{
		model->vertex[z].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
		if (!(model->vertex[z].buffer_data = malloc(sizeof(GLfloat) * model->vertex[z].size_data)))
			return (false);
		model->uv[z].size_data = obj.groupe[iGroupe].faces.len * 2 * 3;
		if (!(model->uv[z].buffer_data = malloc(sizeof(GLfloat) * model->uv[z].size_data)))
			return (false);
		model->normal[z].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
		if (!(model->normal[z].buffer_data = malloc(sizeof(GLfloat) * model->normal[z].size_data)))
			return (false);
		model->colorTriangles[z].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
		if (!(model->colorTriangles[z].buffer_data = malloc(sizeof(GLfloat) * model->colorTriangles[z].size_data)))
			return (false);
		model->colorFaces[z].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
		if (!(model->colorFaces[z].buffer_data = malloc(sizeof(GLfloat) * model->colorFaces[z].size_data)))
			return (false);
		iGroupe++;
		z++;
	}
	return (true);
}

void	readVertex(t_vertex vertex, t_bufferData *buffer, size_t i)
{
	buffer->buffer_data[i] = (GLfloat)vertex.x;
	buffer->buffer_data[i + 1] = (GLfloat)vertex.y;
	buffer->buffer_data[i + 2] = (GLfloat)vertex.z;
}

void	readUv(t_uv uv, t_bufferData *buffer, size_t i)
{
	buffer->buffer_data[i] = (GLfloat)uv.u;
	buffer->buffer_data[i + 1] = (GLfloat)uv.v;
}

bool	getUvBuffer(t_triangle triangle, t_uv_array uv, t_bufferData *uvBuffer, size_t i)
{
	if (triangle.a.indexUv > uv.len || triangle.b.indexUv > uv.len || triangle.c.indexUv > uv.len)
		return (false);
	readUv(uv.this[triangle.a.indexUv], uvBuffer, i);
	readUv(uv.this[triangle.b.indexUv], uvBuffer, i + 2);
	readUv(uv.this[triangle.c.indexUv], uvBuffer, i + 4);
	return (true);
}

bool	getVerticesBuffer(t_triangle triangle, t_vertex_array vertices, t_bufferData *vertexBuffer, size_t i)
{
	if (triangle.a.indexVertex > vertices.len || triangle.b.indexVertex > vertices.len
		|| triangle.c.indexVertex > vertices.len)
		return (false);
	readVertex(vertices.this[triangle.a.indexVertex], vertexBuffer, i);
	readVertex(vertices.this[triangle.b.indexVertex], vertexBuffer, i + 3);
	readVertex(vertices.this[triangle.c.indexVertex], vertexBuffer, i + 6);
	return (true);
}

bool	getNormalBuffer(t_triangle triangle, t_vertex_array normal, t_bufferData *normalBuffer, size_t i)
{
	if (triangle.a.indexNormal > normal.len || triangle.b.indexNormal > normal.len
		|| triangle.c.indexNormal > normal.len)
		return (false);
	readVertex(normal.this[triangle.a.indexNormal], normalBuffer, i);
	readVertex(normal.this[triangle.b.indexNormal], normalBuffer, i + 3);
	readVertex(normal.this[triangle.c.indexNormal], normalBuffer, i + 6);
	return (true);
}

void	getStaticUv(t_bufferData *uvBuffer, t_bufferData vertexBuffer)
{
	t_vec3	maxVec;
	t_vec3	minVec;
	size_t	i;
	size_t	j;

	minVec = (t_vec3){vertexBuffer.buffer_data[0], vertexBuffer.buffer_data[1], vertexBuffer.buffer_data[2]};
	maxVec = (t_vec3){vertexBuffer.buffer_data[0], vertexBuffer.buffer_data[1], vertexBuffer.buffer_data[2]};
	i = 3;
	while (i < vertexBuffer.size_data)
	{
		if (vertexBuffer.buffer_data[i + 1] > maxVec.x)
			maxVec.x = vertexBuffer.buffer_data[i + 1];
		if (vertexBuffer.buffer_data[i + 1] < minVec.x)
			minVec.x = vertexBuffer.buffer_data[i + 1];
		if (vertexBuffer.buffer_data[i + 2] > maxVec.y)
			maxVec.y = vertexBuffer.buffer_data[i + 2];
		if (vertexBuffer.buffer_data[i + 2] < minVec.y)
			minVec.y = vertexBuffer.buffer_data[i + 2];
		i += 3;
	}
	i = 0;
	j = 0;
	while (i < uvBuffer->size_data)
	{
		if (minVec.x == maxVec.x)
			uvBuffer->buffer_data[i] = 0;
		else
			uvBuffer->buffer_data[i] = (vertexBuffer.buffer_data[j + 2] - minVec.x) / (maxVec.x - minVec.x);
		if (minVec.y == maxVec.y)
			uvBuffer->buffer_data[i + 1] = 0;
		else
			uvBuffer->buffer_data[i + 1] = (vertexBuffer.buffer_data[j + 1] - minVec.y) / (maxVec.y - minVec.y);
		i += 2;
		j += 3;
	}
}

void	getTriangleColorBuffer(t_bufferData *colorBuffer)
{
	size_t	i;
	size_t	z;

	i = 0;
	z = 0;
	while (i < colorBuffer->size_data)
	{
		colorBuffer->buffer_data[i] = (color[z % 20]).x / 255;
		colorBuffer->buffer_data[i + 1] = (color[z % 20]).y / 255;
		colorBuffer->buffer_data[i + 2] = (color[z % 20]).z / 255;
		colorBuffer->buffer_data[i + 3] = (color[z % 20]).x / 255;
		colorBuffer->buffer_data[i + 4] = (color[z % 20]).y / 255;
		colorBuffer->buffer_data[i + 5] = (color[z % 20]).z / 255;
		colorBuffer->buffer_data[i + 6] = (color[z % 20]).x / 255;
		colorBuffer->buffer_data[i + 7] = (color[z % 20]).y / 255;
		colorBuffer->buffer_data[i + 8] = (color[z % 20]).z / 255;
		i += 9;
		z++;
	}
}

void	getFacesColorBuffer(t_bufferData *colorBuffer, t_facesPerLine fpl)
{
	size_t	i;
	size_t	z;
	size_t	y;
	size_t	c;

	i = 0;
	z = 0;
	y = 0;
	while (y < fpl.len)
	{
		while (z < fpl.this[y])
		{
			colorBuffer->buffer_data[i] = (color[c % 19]).x / 255;
			colorBuffer->buffer_data[i + 1] = (color[c % 19]).y / 255;
			colorBuffer->buffer_data[i + 2] = (color[c % 19]).z / 255;
			colorBuffer->buffer_data[i + 3] = (color[c % 19]).x / 255;
			colorBuffer->buffer_data[i + 4] = (color[c % 19]).y / 255;
			colorBuffer->buffer_data[i + 5] = (color[c % 19]).z / 255;
			colorBuffer->buffer_data[i + 6] = (color[c % 19]).x / 255;
			colorBuffer->buffer_data[i + 7] = (color[c % 19]).y / 255;
			colorBuffer->buffer_data[i + 8] = (color[c % 19]).z / 255;
			i += 9;
			z++;
		}
		z = 0;
		c++;
		y++;
	}
}

bool	readBuffers(t_obj obj, t_model *model)
{
	size_t	i;
	size_t	y;
	size_t	z;
	size_t	t;

	i = 0;
	t = 0;
	z = 0;
	if (obj.len > 1)
		i = 1;
	while (i < obj.len)
	{
		y = 0;
		if (obj.groupe[i].name)
		{
			if (!(model->vertex[z].name = malloc(sizeof(char) * (strlen(obj.groupe[i].name) + 1))))
				return (false);
			model->vertex[z].name = strcpy(model->vertex[z].name, obj.groupe[i].name);
		}
		else
			model->vertex[z].name = NULL;
		while (y < obj.groupe[i].faces.len)
		{
			if (!getVerticesBuffer(obj.groupe[i].faces.triangle[y], obj.vertex, &(model->vertex[z]), y * 9))
				return (false);
			if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Normal_Type)
			{
				if (!getNormalBuffer(obj.groupe[i].faces.triangle[y], obj.vn, &(model->normal[z]), y * 9))
					return (false);
			}
			if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Texture_Type)
			{
				if (!getUvBuffer(obj.groupe[i].faces.triangle[y], obj.vt, &(model->uv[z]), y * 6))
					return (false);
			}
			y++;
			t++;
		}
		getTriangleColorBuffer(&(model->colorTriangles[z]));
		getFacesColorBuffer(&(model->colorFaces[z]), obj.groupe[i].faces.fpl);
		if (obj.type != Obj_Vertex_Texture_Normal_Type && obj.type != Obj_Texture_Type)
		{
			getStaticUv(&(model->uv[z]), model->vertex[z]);
		}
		z++;
		i++;
	}
	return (true);
}

void	printModel(t_model model, t_face_type type)
{
	size_t	i;
	size_t	y;

	i = 0;
	printf("size_groupe : %zu\n", model.size_groupe);
	while (i < model.size_groupe)
	{
		if (model.vertex[i].name)
			printf("%s\n", model.vertex[i].name);
		y = 0;
		while (y < model.vertex[i].size_data)
		{
			printf("%zu ", y);
			printf("%f ", model.vertex[i].buffer_data[y]);
			printf("%f ", model.vertex[i].buffer_data[y++]);
			printf("%f \n", model.vertex[i].buffer_data[y++]);
			y++;
		}
		if (type == Obj_Vertex_Texture_Normal_Type || type == Obj_Normal_Type)
		{
			y = 0;
			while (y < model.normal[i].size_data)
			{
				printf("%zu   ", y);
				printf("%f ", model.normal[i].buffer_data[y]);
				printf("%f ", model.normal[i].buffer_data[y++]);
				printf("%f \n", model.normal[i].buffer_data[y++]);
				y++;
			}
		}
		if (type == Obj_Vertex_Texture_Normal_Type || type == Obj_Texture_Type)
		{
			y = 0;
			while (y < model.uv[i].size_data)
			{
				printf("%zu   ", y);
				printf("%f ", model.uv[i].buffer_data[y]);
				printf("%f ", model.uv[i].buffer_data[y++]);
				printf("%f \n", model.uv[i].buffer_data[y++]);
				y++;
			}
		}
		i++;
	}
}

void	freeObj(t_obj *obj)
{
	size_t	i;

	i = 0;
	if (obj->vertex.this)
		free(obj->vertex.this);
	if (obj->vn.this)
		free(obj->vn.this);
	if (obj->vt.this)
		free(obj->vt.this);
	while (i < obj->len)
	{
		if (obj->groupe[i].faces.triangle)
			free(obj->groupe[i].faces.triangle);
		if (obj->groupe[i].faces.fpl.this)
			free(obj->groupe[i].faces.fpl.this);
		if (obj->groupe[i].name)
			free(obj->groupe[i].name);
		i++;
	}
	free(obj->groupe);
}

int	getModel(char *filename, t_model *model)
{
	t_obj_reader	reader;
	t_obj			obj;
	int				ret;
	size_t			i;

	if ((ret = obj_read(&obj, filename, &reader)) != GET_RESULT)
	{
		if (ret != RIP_OPEN)
			freeObj(&obj);
		printError(reader, ret);
		return (ret);
	}
	i = 0;
	if (obj.groupe[0].name == NULL && obj.len > 1)
		i = 1;
	while (i < obj.len)
	{
		if (obj.groupe[i].faces.len < 1)
			return (NO_FACES);
		i++;
	}
	if (!initBuffer(obj, model))
		return (MALLOCINITBUFFERFAILED);
	if (!readBuffers(obj, model))
	{
		return (READBUFFERFAILED);
	}
	freeObj(&obj);
	return (GET_RESULT);
}
