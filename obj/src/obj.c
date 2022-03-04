/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:10:35 by cmace             #+#    #+#             */
/*   Updated: 2022/03/04 17:21:30 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

int	printError(t_obj_reader self, int error)
{
	int	ret;
	printf("Line : %zu\n", self.line);
	printf("Col : %zu\n", self.column);
	if (error == WRONG_CHAR || error == NO_RESULT)
	{
		write(2, " char : ", 8);
		if ((ret = obj_reader_peek(&self)) <= -1)
			error = RIP_READ;
		else if (ret == '\n' || ret == 0)
			write(2, "'\\n' OR 'EOF'. Need more data\n", 31);
		else if (ret >= 7 && ret <= 13)
			write(2, "Non readable\n", 14);
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
	int16_t	c;
	int		ret;

	ret = obj_reader_next(reader);
	c = obj_reader_peek(reader);
	if (c == ' ' || c == '\t')
		ret = obj_get_vertex(&obj->vertex, reader);
	else if (c == 'n')
	{
		if ((ret = obj_reader_next(reader)) != GET_RESULT)
			return (ret);
		ret = obj_get_vertex(&obj->vn, reader);
	}
	else if (c == 't')
	{
		if ((ret = obj_reader_next(reader)) != GET_RESULT)
			return (ret);
		ret = obj_get_uv(&obj->vt, reader);
	}
	else
		ret = c == -1 ? RIP_READ : WRONG_CHAR;
	if (ret != GET_RESULT)
		return (ret);
	if ((ret = obj_skip_nl(reader)) != GET_RESULT)
	{
		return (ret);
	}
	return (ret);
}

static int	obj_read_type(t_obj *obj, t_groupe **currentGroupe, t_obj_reader *reader)
{
	int16_t	c;
	int		ret;

	ret = GET_RESULT;
	c = obj_reader_peek(reader);
	if (c == 'v')
	{
		ret = obj_get_vertex_type(obj, reader);
		if (ret != GET_RESULT)
		{
			return (ret);
		}
	}
	else if (c == 'f')
	{
		if (((ret = obj_reader_next(reader)) != GET_RESULT)
			|| (ret = obj_get_triangles_index(&(*currentGroupe)->faces, &obj->type, reader)) != GET_RESULT)
		{
			return (ret);
		}
	}
	else if (c == 'g')
	{
		if (((ret = obj_reader_next(reader)) != GET_RESULT)
			|| (ret = obj_get_groupe(obj, currentGroupe, reader)) != GET_RESULT)
		{
			return (ret);
		}
	}
	else if (c == 's' || c == 'm' || c == 'u' || c == 'o' || c == '#' || c == '\n')
	{
		if ((ret = obj_skip_nl(reader)) != GET_RESULT)
		{
			return (ret);
		}
	}
	else
		ret = c <= -1 ? RIP_READ : WRONG_CHAR;
	return (ret);
}

int	obj_read(t_obj *obj, char *filepath, t_obj_reader *reader)
{
	char		buffer[4096];
	int16_t		c;
	int			ret;
	t_groupe	*currentGroupe;

	ret = GET_RESULT;
	if ((*reader = obj_create_reader(open(filepath, O_RDONLY), buffer, 4096)).fd <= 0)
		return (RIP_OPEN);
	if (!(*obj = create_groupe(1, Obj_No_Type)).groupe)
		return (RIP_MALLOC);
	if (!(obj->vertex = create_vertex_array(10)).this
		|| !(obj->vn = create_vertex_array(10)).this
		|| !(obj->vt = create_uv_array(10)).this
		|| !(currentGroupe = obj_append_groupe(obj, (t_groupe){
			.name = NULL,
			.faces = create_triangle_array(10)
		})) || !(currentGroupe->faces.fpl = create_fpl_array(10)).this)
	{
		return (RIP_MALLOC);
	}
	printf("start lecture file\n");
	while ((c = obj_reader_peek(reader)) > 0)
	{
		ret = obj_read_type(obj, &currentGroupe, reader);
		if (ret != GET_RESULT)
			return (ret);
		c = obj_reader_next(reader);
	}
	printf("end lecture file\n");
	if (c <= -1)
		return (RIP_READ);
	if (obj->vertex.len < 1)
		return (NO_VERTEX);
	return (ret);
}
