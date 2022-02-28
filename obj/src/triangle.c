#include "obj.h"

int obj_read_triangle_point_index(t_triangle_point *point, t_face_type *type, t_obj_reader *reader)
{
	int ret;
	bool test;

	if ((ret = obj_vertex_type(&point->indexVertex, type, reader)) != GET_RESULT || *type == Obj_Vertex_Type)
	{
		return (ret);
	}
	// if ((ret = obj_reader_next(reader)) != GET_RESULT)
	// 	return (ret);
	if ((ret = obj_uv_type(&point->indexUv, type, reader, &test)) != GET_RESULT || *type == Obj_Texture_Type)
	{
		return (ret);
	}
	// if ((ret = obj_reader_next(reader)) != GET_RESULT)
	// 	return (ret);
	if ((ret = obj_normal_type(&point->indexNormal, type, reader, &test)) != GET_RESULT)
	{
		return (ret);
	}
	return (GET_RESULT);
}

int obj_read_triangle(t_triangle *triangle, t_face_type *type, t_obj_reader *reader)
{
	int ret;

	ret = obj_skip_whitespace(reader);
	triangle->b = triangle->c;
	ret = obj_read_triangle_point_index(&triangle->c, type, reader);
	return ret;
}

int obj_append_fpl(t_facesPerLine *tabfpl, size_t fpl)
{
	size_t new_size;
	size_t *new;

	if (tabfpl->len == tabfpl->size)
	{
		new_size = tabfpl->size * 2;
		if (!(new = (size_t *)malloc(sizeof(size_t) * new_size)))
			return (RIP_MALLOC);
		ft_memcpy(new, tabfpl->this, sizeof(size_t) * tabfpl->size);
		free(tabfpl->this);
		tabfpl->this = new;
		tabfpl->size = new_size;
	}
	tabfpl->this[tabfpl->len++] = fpl;
	return (GET_RESULT);
}

int obj_get_triangles_index(t_faces_array *faces, t_face_type *type, t_obj_reader *reader)
{
	int ret;
	int16_t c;
	t_triangle_point sommet[3];
	t_triangle triangle;
	int i;
	size_t y;

	i = 0;
	c = obj_reader_peek(reader);
	y = 1;
	while (i < 3)
	{
		ret = obj_skip_whitespace(reader);
		if (ret != GET_RESULT)
			return (ret);
		if ((ret = obj_read_triangle_point_index(&sommet[i], type, reader)) != GET_RESULT)
			return (ret);
		i++;
	}
	c = obj_reader_peek(reader);
	triangle = (t_triangle){
		.a = sommet[0],
		.b = sommet[1],
		.c = sommet[2]};
	ret = obj_append_triangle(faces, triangle);
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	while ((c = obj_reader_peek(reader)) != '\n' && c != 0)
	{
		ret = obj_skip_whitespace(reader);
		if ((ret = obj_read_triangle(&triangle, type, reader)) != GET_RESULT)
			return ret;
		ret = obj_append_triangle(faces, triangle);
		ret = obj_skip_whitespace(reader);
		if (ret != GET_RESULT)
			return (ret);
		y++;
	}
	if ((ret = obj_append_fpl(&faces->fpl, y)) != GET_RESULT)
		return (ret);
	return (ret);
}