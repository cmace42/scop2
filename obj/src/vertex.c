#include "obj.h"


int obj_read_part_int(float *value, t_obj_reader *reader, int *sign)
{
	int16_t c;
	int ret;

	*value = 0;
	*sign = 1;
	ret = GET_RESULT;
	c = obj_reader_peek(reader);
	if (c == '-')
	{
		*sign = -1;
		ret = obj_reader_next(reader);
	}
	else if (c == '+')
		ret = obj_reader_next(reader);
	while ((c = obj_reader_peek(reader)) >= '0' && c <= '9')
	{
		*value = *value * 10.0 + (c - '0');
		ret = obj_reader_next(reader);
		if (ret != GET_RESULT)
			return (RIP_READ);
	}
	return (c == -1 ? RIP_READ : ret);
}

int obj_read_part_float(float *value, t_obj_reader *reader)
{
	int16_t c;
	int ret;
	int i;

	*value = 0;
	i = 0;
	ret = GET_RESULT;
	while ((c = obj_reader_peek(reader)) >= '0' && c <= '9')
	{
		*value = (*value * 10.0) + (c - '0');
		ret = obj_reader_next(reader);
		if (ret != GET_RESULT)
			return (ret);
		i++;
	}
	while (i--)
		*value *= 0.1;
	return (c == -1 ? RIP_READ : GET_RESULT);
}

int obj_read_float(float *value, t_obj_reader *reader)
{
	int sign;
	int ret;
	int16_t c;
	float res;

	ret = GET_RESULT;
	sign = 1;
	c = obj_reader_peek(reader);
	if ((c < '0' && c > '9') && c != '-' && c != '+')
		return (c == -1 ? RIP_READ : WRONG_CHAR);
	if ((ret = obj_read_part_int(value, reader, &sign)) == GET_RESULT)
	{
		c = obj_reader_peek(reader);
		if (c == '.')
			ret = obj_reader_next(reader);
		else if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
			return (GET_RESULT);
		else
			return (WRONG_CHAR);
		if ((ret = obj_read_part_float(&res, reader)) == GET_RESULT)
			*value = (*value + res) * (float)sign;
		c = obj_reader_peek(reader);
		if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
			return (WRONG_CHAR);
	}
	return (c == -1 ? RIP_READ : ret);
}

int obj_get_uv(t_uv_array *uv_array, t_obj_reader *reader)
{
	int ret;
	t_uv uv;
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_read_float(&uv.u, reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_read_float(&uv.v, reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_read_float(&uv.w, reader);
	if (ret != GET_RESULT)
		return (ret);
	return (obj_append_uv(uv_array, uv));
}

int obj_get_vertex(t_vertex_array *vertex_array, t_obj_reader *reader)
{
	int ret;
	t_vertex v;
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_read_float(&v.x, reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_read_float(&v.y, reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_skip_whitespace(reader);
	if (ret != GET_RESULT)
		return (ret);
	ret = obj_read_float(&v.z, reader);
	if (ret != GET_RESULT)
		return (ret);
	return (obj_append_vertex(vertex_array, v));
}