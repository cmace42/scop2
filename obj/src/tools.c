#include "obj.h"

int obj_skip_nl(t_obj_reader *self)
{
	int16_t c;
	int ret;
	
	while((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		ret = obj_reader_next(self);
	}
	if (c == -1)
		return (RIP_READ);
	return (ret);
}

int obj_skip_whitespace(t_obj_reader *self)
{
	int16_t c;
	int ret;

	while((c = obj_reader_peek(self)) == ' ' || c == '\t' || c == '\r')
	{
		ret = obj_reader_next(self);
	}
	if (c == -1)
		return (RIP_READ);
	return (ret);
}

void printvertex(t_vertex_array v_array)
{
	size_t i;
	i = 0;
	while (i < v_array.size)
	{
		printf("%f %f %f\n", v_array.this[i].x, v_array.this[i].y, v_array.this[i].z);
		i++;
	}
}