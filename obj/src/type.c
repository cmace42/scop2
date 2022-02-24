#include "obj.h"

static int control_type(t_face_type *type, t_face_type new_type)
{
	if (*type == Obj_No_Type)
	{
		*type = new_type;
	}
	else if (*type != new_type)
	{
		return (WRONG_TYPE);
	}
    return (GET_RESULT);
}

int	obj_vertex_type(size_t *vertex, t_face_type *type, t_obj_reader *reader)
{
	int unusedSign;
	int16_t c;
	int ret;
	float res;

	c = obj_reader_peek(reader);
	if (c < '0' || c > '9')
	{
		return (c <= -1 ? RIP_READ : WRONG_CHAR);
	}
	ret = obj_read_part_int(&res, reader, &unusedSign);
	*vertex = (size_t)res - 1;
	c = obj_reader_peek(reader);
	if ((c) == ' ' || c == '\t' || c == '\r' || c == '\n' || c == 0)
	{
		if ((ret = control_type(type, Obj_Vertex_Type)) != GET_RESULT)
			return(WRONG_VERTEX_TYPE_IN_FACE);
		return (GET_RESULT);
	}
	else if (c != '/')
		return (c <= -1 ? RIP_READ : WRONG_CHAR);
	return (GET_RESULT);
}

int	obj_uv_type(size_t *uv, t_face_type *type, t_obj_reader *reader, bool *haveNormal)
{
	int unusedSign;
	int16_t c;
	int ret;
	float res;

	*haveNormal = false;
	obj_reader_next(reader);
	c = obj_reader_peek(reader);
	if (c == '/')
	{
		if ((ret = control_type(type, Obj_Normal_Type)) != GET_RESULT)
			return(WRONG_NORMAL_TYPE_IN_FACE);
		*haveNormal = true;
	}
	else 
	{
		if (c < '0' || c > '9')
			return (c == -1 ? RIP_READ : WRONG_CHAR);
		if ((ret = obj_read_part_int(&res, reader, &unusedSign)) != GET_RESULT)
			return (ret);
		*uv = (size_t)res - 1;
	}
	c = obj_reader_peek(reader);
	if ((c) == ' ' || c == '\t' || c == '\r' || c == '\n' || c == 0)
	{
		*haveNormal = false;
		if ((ret = control_type(type, Obj_Texture_Type)) != GET_RESULT)
			return(WRONG_VERTEX_TYPE_IN_FACE);
		return (GET_RESULT);
	}
	else if (c != '/')
		return (c <= -1 ? RIP_READ : WRONG_CHAR);
	return (GET_RESULT);
}

int obj_normal_type(size_t *normal, t_face_type *type, t_obj_reader *reader, bool *haveNormal)
{
	int unusedSign;
	int16_t c;
	int ret;
	float res;

	obj_reader_next(reader);
	c = obj_reader_peek(reader);
	if (c < '0' || c > '9')
		return (c <= -1 ? RIP_READ : WRONG_CHAR);
	ret = obj_read_part_int(&res, reader, &unusedSign);
	*normal = (size_t)res - 1;
	if (!*haveNormal)
	{
		if ((ret = control_type(type, Obj_Vertex_Texture_Normal_Type)) != GET_RESULT)
			return(WRONG_VERTEX_TYPE_IN_FACE);
	}
	return (GET_RESULT);
}