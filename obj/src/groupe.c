#include "obj.h"

int obj_append_char(int8_t c, char **name, size_t *size, size_t i)
{
	size_t new_size;
	char *new;

	if (i == *size)
	{
		new_size = *size * 2;
		if (!(new = (char*)malloc(sizeof(char) * new_size)))
			return (RIP_MALLOC);
		memcpy(new, *name, sizeof(char) * *size);
		free(*name);
		*name = new;
		*size = new_size;
	}
	(*name)[i] = c;
	return (GET_RESULT);
}

int obj_read_name(char **name, t_obj_reader *reader)
{
	int8_t c;
	size_t i;
	size_t size;

	i = 0;
	size = 10;
	if (!(*name = (char*)malloc(sizeof(char) * size)))
		return (RIP_MALLOC);
	while((c = obj_reader_peek(reader)) != '\n' && c > 0)
	{
		if (obj_append_char(c, name, &size, i) != GET_RESULT)
			return (RIP_MALLOC);
		if (obj_reader_next(reader) != GET_RESULT)
			return (RIP_READ);
		i++;
	}
	if (obj_append_char('\0', name, &size, i) != GET_RESULT)
		return (RIP_MALLOC);
	return (c == -1 ? RIP_READ : GET_RESULT);
}

int obj_read_groupe(t_groupe *newGroupe, t_obj_reader *reader)
{
	int ret;
	if (obj_skip_whitespace(reader) == GET_RESULT)
	{
		if (obj_reader_peek(reader) == '\n')
			return (WRONG_CHAR);
		if ((ret = obj_read_name(&newGroupe->name, reader)) != GET_RESULT)
			return (ret);
	}
	return (GET_RESULT);
}

int obj_get_groupe(t_obj *obj, t_groupe **currentGroupe, t_obj_reader *reader)
{
	// t_faces_array faces;
	int ret;
	
	if (!(*currentGroupe = obj_append_groupe(obj, **currentGroupe)))
	{
		// free(faces.triangle);
		return (RIP_MALLOC);
	}
	if (!((**currentGroupe).faces = create_triangle_array(10)).triangle
		|| !((**currentGroupe).faces.fpl = create_fpl_array(10)).this)
		return (RIP_MALLOC);
	if ((ret = obj_read_groupe(*currentGroupe, reader)) != GET_RESULT)
		return (ret);
	return GET_RESULT;
}