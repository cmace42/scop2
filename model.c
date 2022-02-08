#include "scop.h"

bool initBuffer(t_obj obj, t_model *model)
{
	size_t iGroupe;
	size_t len;

	iGroupe = 0;
	if (obj.len > 1)
		len = obj.len - 1;
	else
		len = obj.len;
	if (!(model->vertex = malloc(sizeof(t_bufferData) * len)))
		return (false);
	if ((obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Texture_Type))
		if (!(model->uv = malloc(sizeof(t_bufferData) * len)))
			return (false);
	if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Normal_Type)
		if (!(model->normal = malloc(sizeof(t_bufferData) * len)))
			return (false);
	while (iGroupe < len)
	{
		model->vertex[iGroupe].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
		if  (!(model->vertex[iGroupe].buffer_data = malloc(sizeof(GLfloat) * model->vertex[iGroupe].size_data)))
			return (false);
		if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Texture_Type)
		{
			model->uv[iGroupe].size_data = obj.groupe[iGroupe].faces.len * 2 * 3;
			if (!(model->uv[iGroupe].buffer_data = malloc(sizeof(GLfloat) * model->uv[iGroupe].size_data)))
				return (false);
		}
		if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Normal_Type)
		{
			model->normal[iGroupe].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
			if (!(model->normal[iGroupe].buffer_data = malloc(sizeof(GLfloat) * model->normal[iGroupe].size_data)))
				return (false);
		}
		iGroupe++;
	}
	return (true);
}

void readVertex(t_vertex vertex, t_bufferData *buffer, size_t i)
{
	buffer->buffer_data[i] = vertex.x;
	buffer->buffer_data[i + 1] = vertex.y;
	buffer->buffer_data[i + 2] = vertex.z;
}

void getVerticesBuffer(t_triangle triangle, t_vertex_array vertices, t_bufferData *vertexBuffer, size_t i)
{
	readVertex(vertices.this[triangle.a.indexNormal], vertexBuffer, i);
	readVertex(vertices.this[triangle.b.indexNormal], vertexBuffer, i + 3);
	readVertex(vertices.this[triangle.c.indexNormal], vertexBuffer, i + 6);
}

bool readBuffers(t_obj obj, t_model *model)
{
	size_t i;
	int noGroupe;
	size_t y;

	noGroupe = 0;

	if (obj.len > 1)
		noGroupe = -1;
	i = 0;
	y = 0;
	while (i < obj.len)
	{
		vertexBuffer->name = groupe[i].name;
		while(y < obj.groupe[i].faces.len)
		{
			getVertexBuffer(obj.groupe[i].faces, obj.vertex, model->vertex);
			if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Normal_Type)
				getVerticesBuffer(obj.groupe[i].faces, obj.normal, model->normal);
			y++;
		}
		y = 0;
		i++;
	}
}

bool getBuffersModel(t_obj obj, t_model *model)
{
	if (!initBuffer(obj, model))
		return (false);
	
	return (true);
}

bool getModel(char *filename, t_model *model)
{
	t_obj_reader reader;
	t_obj obj;
	int ret;
	
	if ((ret = obj_read(&obj, filename, &reader)) != GET_RESULT)
	{
		printError(reader, ret);
		return (false);
	}
	if (getBuffersModel(obj, model) == false)
		return (false);
	// printobj(obj);
	model = NULL;
	if (model)
		model = NULL;
	return (true);
}