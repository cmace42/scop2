#include "obj.h"

int obj_read(t_obj *obj, char *filepath)
{
	t_obj_reader reader;
	char buffer[4096];
	int16_t c;
	if ((reader = obj_create_reader(open(filepath, O_RDONLY),buffer, 4096)).fd  <= 0)
		return(RIP_OPEN);
	if (!(obj->vertex = create_vertex_array(10)).this
		|| !(obj->vn = create_vertex_array(10)).this
		|| !(obj->vt = create_uv_array(10)).this)
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

int	obj_read_type(t_obj *obj, t_obj_reader *reader)
{
	int16_t c;
	int ret;

	if ((c = obj_reader_peek(reader)) == 'v')
	{
		ret = obj_get_vertex_by_type(obj, reader);
		//parse vertex, vt, vn
	}
	else if (c == 'f')
	{
		//parse face
	}
	else if (c == 'g')
	{
		// new groupe
	}
	else if (c == 's' || c == 'm' || c == 'u' || c == 'o' || c == '#')
	{
		
	}
	else
		ret = c == -1 ? RIP_READ : WRONG_CHAR;
	return (ret);
}

int	obj_get_vertex_by_type(t_obj *obj, t_obj_reader *reader)
{
	int16_t c;
	int ret;
	ret = obj_reader_next(reader);
	if ((c = obj_reader_peek(reader)) == ' ' || c == '\t')
	{
		
		// parse vertex
	}
	else if (c == 'n')
	{
		//parse vn
	}
	else if ((c = obj_reader_peek(reader)) == 't')
	{

		//parse uv
	}
	return (ret)
}