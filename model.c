#include "scop.h"

bool initBuffer(t_obj obj, t_model *model)
{
	size_t iGroupe;
	size_t z;

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
	if ((obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Texture_Type))
		if (!(model->uv = malloc(sizeof(t_bufferData) * model->size_groupe)))
			return (false);
	if ((obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Normal_Type))
		if (!(model->normal = malloc(sizeof(t_bufferData) * model->size_groupe)))
			return (false);
	while (iGroupe < obj.len)
	{
		model->vertex[z].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
		if  (!(model->vertex[z].buffer_data = malloc(sizeof(GLfloat) * model->vertex[z].size_data)))
			return (false);
		if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Texture_Type)
		{
			model->uv[z].size_data = obj.groupe[iGroupe].faces.len * 2 * 3;
			if (!(model->uv[z].buffer_data = malloc(sizeof(GLfloat) * model->uv[z].size_data)))
				return (false);
		}
		if (obj.type == Obj_Vertex_Texture_Normal_Type || obj.type == Obj_Normal_Type)
		{
			model->normal[z].size_data = obj.groupe[iGroupe].faces.len * 3 * 3;
			if (!(model->normal[z].buffer_data = malloc(sizeof(GLfloat) * model->normal[z].size_data)))
				return (false);
			
		}
		iGroupe++;
		z++;
	}
	return (true);
}

void readVertex(t_vertex vertex, t_bufferData *buffer, size_t i)
{
	// printf("%zu %f\n",i, vertex.x);
	buffer->buffer_data[i] = (GLfloat)vertex.x;
	buffer->buffer_data[i + 1] = (GLfloat)vertex.y;
	buffer->buffer_data[i + 2] = (GLfloat)vertex.z;
}

void readUv(t_uv uv, t_bufferData *buffer, size_t i)
{
	// printf("%zu %f\n",i, uv.x);
	buffer->buffer_data[i] = (GLfloat)uv.u;
	buffer->buffer_data[i + 1] = (GLfloat)uv.v;
}

bool getUvBuffer(t_triangle triangle, t_uv_array uv, t_bufferData *uvBuffer, size_t i)
{
	if (triangle.a.indexUv > uv.len || triangle.b.indexUv > uv.len ||  triangle.c.indexUv > uv.len)
		return false;
	readUv(uv.this[triangle.a.indexUv], uvBuffer, i);
	readUv(uv.this[triangle.b.indexUv], uvBuffer, i + 2);
	readUv(uv.this[triangle.c.indexUv], uvBuffer, i + 4);
	return true;
}

bool getVerticesBuffer(t_triangle triangle, t_vertex_array vertices, t_bufferData *vertexBuffer, size_t i)
{
	if (triangle.a.indexVertex > vertices.len || triangle.b.indexVertex > vertices.len
		|| triangle.c.indexVertex > vertices.len)
		return false;
	readVertex(vertices.this[triangle.a.indexVertex], vertexBuffer, i);
	readVertex(vertices.this[triangle.b.indexVertex], vertexBuffer, i + 3);
	readVertex(vertices.this[triangle.c.indexVertex], vertexBuffer, i + 6);
	return true;
}

bool getNormalBuffer(t_triangle triangle, t_vertex_array normal, t_bufferData *normalBuffer, size_t i)
{
	if ( triangle.a.indexNormal > normal.len || triangle.b.indexNormal > normal.len
		|| triangle.c.indexNormal > normal.len)
		return false;
	readVertex(normal.this[triangle.a.indexNormal], normalBuffer, i);
	readVertex(normal.this[triangle.b.indexNormal], normalBuffer, i + 3);
	readVertex(normal.this[triangle.c.indexNormal], normalBuffer, i + 6);
	return true;
}


bool readBuffers(t_obj obj, t_model *model)
{
	size_t i;
	size_t y;
	size_t z;
	size_t t;

	i = 0;
	t = 0;
	z = 0;
	// printobj(obj);
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
		while(y < obj.groupe[i].faces.len)
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
					return false;
			}
			y++;
			t++;
		}
		z++;
		i++;
	}
	return true;
}

void printModel(t_model model, t_face_type type)
{
	size_t i;
	size_t y;

	i = 0;
	printf("size_groupe : %zu\n",model.size_groupe);
	while (i < model.size_groupe)
	{
		if (model.vertex[i].name)
			printf("%s\n", model.vertex[i].name);
		y = 0;
		while (y < model.vertex[i].size_data)
		{
			printf("%zu   ",y);
			printf("%f ",model.vertex[i].buffer_data[y]);
			printf("%f ",model.vertex[i].buffer_data[y++]);
			printf("%f \n",model.vertex[i].buffer_data[y++]);
			y++;
		}
		if (type == Obj_Vertex_Texture_Normal_Type || type == Obj_Normal_Type)
		{
			y = 0;
			while(y < model.normal[i].size_data)
			{
				printf("%zu   ",y);
				printf("%f ",model.normal[i].buffer_data[y]);
				printf("%f ",model.normal[i].buffer_data[y++]);
				printf("%f \n",model.normal[i].buffer_data[y++]);
				y++;
			}
		}
		if (type == Obj_Vertex_Texture_Normal_Type || type == Obj_Texture_Type)
		{
			y = 0;
			while(y < model.uv[i].size_data)
			{
				printf("%zu   ",y);
				printf("%f ",model.uv[i].buffer_data[y]);
				printf("%f ",model.uv[i].buffer_data[y++]);
				printf("%f \n",model.uv[i].buffer_data[y++]);
				y++;
			}
		}
		i++;
	}
}

void freeObj(t_obj *obj)
{
	size_t i;

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
		if (obj->groupe[i].name)
			free(obj->groupe[i].name);
		i++;
	}
	free(obj->groupe);
}

bool getModel(char *filename, t_model *model)
{
	t_obj_reader reader;
	t_obj obj;
	int ret;
	size_t i;

	if ((ret = obj_read(&obj, filename, &reader)) != GET_RESULT)
	{
		printError(reader, ret);
		return (false);
	}
	if (obj.vertex.len < 1)
		return (false);
	i = 0;
	if (obj.groupe[0].name == NULL && obj.len > 1)
		i = 1;
	while (i < obj.len)
	{
		if (obj.groupe[i].faces.len < 1)
			return (false);
		i++;
	}
	// printobj(obj);
	if (!initBuffer(obj, model))
		return (false);
	if (!readBuffers(obj, model))
	{
		return (false);
	}
	freeObj(&obj);
	return (true);
}