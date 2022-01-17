#include "obj.h"

int obj_read(t_obj *obj, char *filepath)
{
	t_obj_reader reader;
	char buffer[4096];
	int16_t c;
	if ((reader = obj_create_reader(open(filepath, O_RDONLY),buffer, 4096))
	if (!(obj->vertex = create_vertex_array(10)).this
		|| !(obj->vn = create_vertex_array(10)).this
		|| !(obj.vt = create_uv_array(10)).this))
	{
		return(RIP_MALLOC);
	}
	while((c = obj_reader_peek(&reader)) > 0)
	{
		
		c = obj_reader_next(&reader);
	}
	if (c == -1)
		return (RIP_READ);
}