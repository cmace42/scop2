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

	// printf("%ld %ld\n", vertex_array->len, vertex_array->size);
	if (vertex_array->len == vertex_array->size)
	{
		new_size = vertex_array->size + 10;
		if (!(new = (t_vertex*)malloc(sizeof(t_vertex) * new_size)))
			return (RIP_MALLOC);
		ft_memcpy(new, vertex_array->this, sizeof(t_vertex) * new_size);
		free(vertex_array->this);
		vertex_array->this = new;
		vertex_array->size = new_size;
	}
	vertex_array->this[vertex_array->len++] = vertex;
	return (GET_RESULT);
}

