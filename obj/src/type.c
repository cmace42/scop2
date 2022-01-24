#include "obj.h"

static int control_type(t_face_type *type, t_face_type new_type)
{
	if (*type == Obj_No_Type)
		*type = new_type;
	else if (*type != new_type)
		return (WRONG_TYPE);
    return (DONE);
}

int	obj_vertex_type(size_t *vertex, t_face_type *type, t_obj_reader *reader)
{
	int16_t c;
	int ret;
	float res;

	c = obj_reader_peek(reader);
	if (c < '0' && c > '9')
	{
		return (c == -1 ? RIP_READ : WRONG_CHAR);
	}
	printf("coucou\n");
	ret = obj_read_part_int(&res, reader, NULL);
	*vertex = (size_t)res;
	printf("test\n");
	if ((c = obj_reader_peek(reader)) == ' ' || c == '\t' || c == '\r' || c == '\n')
	{
		if ((ret = control_type(type, Obj_Vertex_Type)) != DONE)
			return(WRONG_VERTEX_TYPE_IN_FACE);
		return (GET_RESULT);
	}
	else if (c != '/')
		return (c == -1 ? RIP_READ : WRONG_CHAR);
	return (GET_RESULT);
}

int	obj_uv_type(size_t *uv, t_face_type *type, t_obj_reader *reader)
{
	int16_t c;
	int ret;
	float res;

	c = obj_reader_peek(reader);
	if (c == '/')
	{
		if ((ret = control_type(type, Obj_Normal_Type)) != DONE)
			return(WRONG_NORMAL_TYPE_IN_FACE);
		return (GET_RESULT);
	}
	else 
	{
		if (c < '0' && c > '9')
			return (c == -1 ? RIP_READ : WRONG_CHAR);
		if ((ret = obj_read_part_int(&res, reader, NULL)) != GET_RESULT)
			return (ret);
	}
	*uv = (size_t)res;
	if ((c = obj_reader_peek(reader)) == ' ' || c == '\t' || c == '\r' || c == '\n')
	{
		if ((ret = control_type(type, Obj_Vertex_Type)) != DONE)
			return(WRONG_VERTEX_TYPE_IN_FACE);
		return (GET_RESULT);
	}
	else if (c != '/')
		return (c == -1 ? RIP_READ : WRONG_CHAR);
	return (GET_RESULT);
}

int obj_normal_type(size_t *normal, t_face_type *type, t_obj_reader *reader)
{
	int16_t c;
	int ret;
	float res;

	c = obj_reader_peek(reader);
	if (c < '0' && c > '9')
		return (c == -1 ? RIP_READ : WRONG_CHAR);
	ret = obj_read_part_int(&res, reader, NULL);
	*normal = (size_t)res;
	if ((ret = control_type(type, Obj_Vertex_Type)) != DONE)
		return(WRONG_VERTEX_TYPE_IN_FACE);
	return (GET_RESULT);
}