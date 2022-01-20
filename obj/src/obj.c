#include "obj.h"

int printError(t_obj_reader *self, int error)
{
	int ret;
	if (error == WRONG_CHAR || error == NO_RESULT)
	{
		write(2, "Error line ", 11);
		printf("%zu\n",self->line);
		write(2, ", col ", 6);
		printf("%zu\n",self->column);
		write(2, " char : ", 8);
		if ((ret = obj_reader_peek(self)) == -1)
		{
			// printf("\n%d\n", ret);
			error = RIP_READ;
		}
		else if (ret == '\n' || ret == 0)
			write(2, "'\\n' OR 'EOF'. Need more data\n", 31);
		else if (ret >= 7 && ret <= 13)
		{
			write(2, "Non readable\n", 14);
		}
		else
		{
			write(2, "'", 1);
			write(2, &ret, 1);
			write(2, "'", 1);
			write(2, "\n", 1);
		}
	}
	else if (error == RIP_MALLOC)
		write(2, "Malloc error.\n", 15);
	else if (error == RIP_OPEN)
		write(2, "Scop can't open this.\n", 23);
	else if (error == RIP_READ)
		write(2, "Something wrong on read.\n", 26);
	else if (error == PREVIOUS_NODE_CANT_BE_NULL)
		write(2, "Previous node in chained list can't be null.\n", 46);
	else if (error == NO_DATA)
		write(2, "Need more data on file.\n", 25);
	else if (error == FACE_ID_OVERFLOW)
		write(2, "Face ID can't be highter than number of vertex.\n", 48);
	else if (error == FACE_ID_CANT_BE_ZERO)
		write(2, "Face ID can't be equals to zero or smaller.\n", 45);
	else if (error == UV_NORMAL_NOT_EQUAL_TO_VERTEX)
		write(2, "Uv or Normal need to be equal to vertex.\n", 42);
	return (error);
}

static int	obj_get_vertex_type(t_obj *obj, t_obj_reader *reader)
{
	int16_t c;
	int ret;
	ret = obj_reader_next(reader);
	c = obj_reader_peek(reader);
	if (c == ' ' || c == '\t')
	{
		ret = obj_get_vertex(&obj->vertex, reader);
		// parse vertex
	}
	else if (c == 'n')
	{
		ret = obj_get_vertex(&obj->vn, reader);	
		//parse vn
	}
	else if (c == 't')
	{

		//parse uv
	}
	else
		ret = c == -1 ? RIP_READ : WRONG_CHAR;
	return (ret);
}

static int	obj_read_type(t_obj *obj, t_obj_reader *reader)
{
	int16_t c;
	int ret;

	ret = 666;
	c = obj_reader_peek(reader);
	if (c == 'v')
	{
		ret = obj_get_vertex_type(obj, reader);
		//parse vertex, vt, vn
	}
	else if (c == 'f')
	{
		ret = obj_get_triangle(obj, reader);
		obj_skip_nl(reader);

		//parse face
	}
	else if (c == 'g')
	{
		ret = GET_RESULT;
		obj_skip_nl(reader);
		// new groupe
	}
	else if (c == 's' || c == 'm' || c == 'u' || c == 'o' || c == '#')
	{
		obj_skip_nl(reader);
		ret = GET_RESULT;
	}
	else
		ret = c == -1 ? RIP_READ : WRONG_CHAR;
	return (ret);
}

int obj_read(t_obj *obj, char *filepath)
{
	t_obj_reader reader;
	char buffer[4096];
	int16_t c;
	int ret;
	ret = 777;
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
		ret = obj_read_type(obj, &reader);
		printError(&reader, ret);
		if (ret != GET_RESULT)
			break;
		c = obj_reader_next(&reader);
	}
	if (c == -1)
		return (RIP_READ);
	return (ret);
}