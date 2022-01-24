#include "obj.h"

int obj_skip_nl(t_obj_reader *self)
{
	int16_t c;
	int ret;

	ret = GET_RESULT;
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

	ret = GET_RESULT;
	while((c = obj_reader_peek(self)) == ' ' || c == '\t' || c == '\r')
	{
		ret = obj_reader_next(self);
	}
	if (c == -1)
		return (RIP_READ);
	return (ret);
}

void printvertex(t_obj obj)
{
	size_t i;

	i = 0;
	printf("v.len : %zu, uv.len %zu, vn.len : %zu\n",obj.vertex.len,obj.vt.len,obj.vn.len);
	if (obj.vertex.len > 0)
	{
		printf("Vertex %zu: \n\n",obj.vertex.len);
		while (i < obj.vertex.len)
		{
			printf("ligne %zu : %f %f %f\n",i, obj.vertex.this[i].x, obj.vertex.this[i].y, obj.vertex.this[i].z);
			i++;
		}
	}
	if (obj.vt.len > 0)
	{
		printf("Uv %zu: \n\n",obj.vt.len);
		i = 0;
		while (i < obj.vt.len)
		{
			printf("ligne %zu : %f %f %f\n",i, obj.vt.this[i].u, obj.vt.this[i].v, obj.vt.this[i].w);
			i++;
		}
	}
	if (obj.vn.len > 0)
	{
		printf("Normal %zu: \n\n",obj.vn.len);
		i = 0;
		while (i < obj.vn.len)
		{
			printf("ligne %zu : %f %f %f\n",i, obj.vn.this[i].x, obj.vn.this[i].y, obj.vn.this[i].z);
			i++;
		}
	}
	
}