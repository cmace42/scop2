#include "obj.h"

int obj_read_triangle_point_index(t_triangle_point *point, t_face_type *type ,t_obj_reader *reader)
{
	int ret;
	
	if ((ret = obj_vertex_type(&point->indexVertex, type, reader)) != GET_RESULT || *type == Obj_Vertex_Type)
		return (ret);
	printf("avant normal type %c\n", obj_reader_peek(reader));
	// if ((ret = obj_reader_next(reader)) != GET_RESULT)
	// 	return (ret);
	if ((ret = obj_uv_type(&point->indexUv, type, reader)) != GET_RESULT || *type == Obj_Texture_Type)
		return (ret);

	// if ((ret = obj_reader_next(reader)) != GET_RESULT)
	// 	return (ret);
	if ((ret = obj_normal_type(&point->indexNormal, type, reader)) != GET_RESULT)
		return (ret);
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

int obj_get_triangles_index(t_faces_array *faces, t_face_type *type, t_obj_reader *reader)
{
	int ret;
	int16_t c;
	t_triangle_point sommet[3];
	t_triangle triangle;
	int i;

	i = 0;
	c = obj_reader_peek(reader);
	while (i < 3)
	{
		printf("bla%c\n",obj_reader_peek(reader));
		ret = obj_skip_whitespace(reader);
		printf("blo%c\n",obj_reader_peek(reader));
		if (ret != GET_RESULT)
			return (ret);
		ret = obj_read_triangle_point_index(&sommet[i], type, reader);
		printf("sommet v  = %zu\n",sommet[i].indexVertex);
		printf("sommet uv = %zu\n",sommet[i].indexUv);
		printf("sommet vn = %zu\n",sommet[i].indexNormal);
		i++;
	}
	c = obj_reader_peek(reader);
	triangle = (t_triangle){
		.a = sommet[0],
		.b = sommet[1],
		.c = sommet[2]
	};
	printf("Hey\n");
	ret = obj_append_triangle(faces, triangle);
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	printf("%c\n",obj_reader_peek(reader));
	while ((c = obj_reader_peek(reader)) != '\n')
	{
		printf("mdr\n");
		if ((ret = obj_read_triangle(&triangle, type, reader)) != GET_RESULT)
			return ret;
		ret = obj_append_triangle(faces, triangle);
		ret = obj_reader_next(reader);
	}
	return (ret);
}