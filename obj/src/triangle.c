#include "obj.h"

int obj_read_triangle_point_index(t_triangle_point *point, t_face_type *type ,t_obj_reader *reader)
{
	uint16_t c;
	int ret;
	
	if ((ret = obj_vertex_type(&point->indexVertex, type, reader)) != GET_RESULT)
		return (ret);
	if ((ret = obj_reader_next(reader)) != GET_RESULT)
		return (ret);
	if ((ret = obj_uv_type(&point->indexUv, type, reader)) != GET_RESULT)
		return (ret);
	if ((ret = obj_reader_next(reader)) != GET_RESULT)
		return (ret);
	if ((ret = obj_normal_type(&point->indexNormal, type, reader)) != GET_RESULT)
		return (ret);
}

int obj_read_triangle(t_triangle *triangle, t_obj_reader *reader)
{
	
}

int obj_get_triangles_index(t_faces_array *faces, t_face_type *type, t_obj_reader *reader)
{
	int ret;
	t_triangle_point sommet[3];
	t_triangle triangle;
	int i;

	i = 0;
	while (i < 3)
	{
		ret = obj_skip_whitespace(reader);
		if (ret != GET_RESULT)
				return (ret);
		ret = obj_read_triangle_point_index(&sommet[i], type,reader);
	}
	triangle = (t_triangle){
		.a = sommet[1],
		.b = sommet[2],
		.c = sommet[3]
	};
	ret = obj_read_triangle(&triangle, reader);
	ret = obj_append_triangle(faces, triangle);
	return (ret);
}