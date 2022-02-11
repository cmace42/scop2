#include "obj.h"
void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*c_src = src;
	char		*c_dst;

	c_dst = dst;
	while (n--)
	{
		*c_dst++ = *c_src++;
	}
	return (dst);
}

int obj_append_vertex(t_vertex_array *vertex_array, t_vertex vertex)
{
	size_t new_size;
	t_vertex *new;

	if (vertex_array->len == vertex_array->size)
	{
		new_size = vertex_array->size * 2;
		if (!(new = (t_vertex*)malloc(sizeof(t_vertex) * new_size)))
			return (RIP_MALLOC);
		ft_memcpy(new, vertex_array->this, sizeof(t_vertex) * vertex_array->size);
		free(vertex_array->this);
		vertex_array->this = new;
		vertex_array->size = new_size;
	}
	vertex_array->this[vertex_array->len++] = vertex;
	return (GET_RESULT);
}

int obj_append_uv(t_uv_array *uv_array, t_uv uv)
{
	size_t new_size;
	t_uv *new;

	// printf("%ld %ld\n", uv_array->len, uv_array->size);
	if (uv_array->len == uv_array->size)
	{
		new_size = uv_array->size * 2;
		if (!(new = (t_uv*)malloc(sizeof(t_uv) * new_size)))
			return (RIP_MALLOC);
		memcpy(new, uv_array->this, sizeof(t_uv) * uv_array->size);
		free(uv_array->this);
		uv_array->this = new;
		uv_array->size = new_size;
	}
	uv_array->this[uv_array->len++] = uv;
	return (GET_RESULT);
}

int obj_append_triangle(t_faces_array *faces, t_triangle triangle)
{
	size_t new_size;
	t_triangle *new;

	// printf("%ld %ld\n", faces->len, faces->size);
	if (faces->len == faces->size)
	{
		new_size = faces->size * 2;
		if (!(new = (t_triangle*)malloc(sizeof(t_triangle) * new_size)))
			return (RIP_MALLOC);
		memcpy(new, faces->triangle, sizeof(t_triangle) * faces->size);
		free(faces->triangle);
		faces->triangle = new;
		faces->size = new_size;
	}
	faces->triangle[faces->len++] = triangle;
	return (GET_RESULT);
}

t_groupe *obj_append_groupe(t_obj *obj, t_groupe groupe)
{
	size_t new_size;
	t_groupe *new;

	// printf("in append groupe %ld\n", obj->len);
	if (obj->len == obj->size)
	{
		new_size = obj->size * 2;
		if (!(new = (t_groupe*)malloc(sizeof(t_groupe) * new_size)))
			return (NULL);
		memcpy(new, obj->groupe, sizeof(t_groupe) * obj->size);
		free(obj->groupe);
		obj->groupe = new;
		obj->size = new_size;
	}
	obj->groupe[obj->len] = groupe;
	return (obj->groupe + obj->len++);
}
