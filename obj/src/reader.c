/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:10:32 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 15:15:51 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_obj_reader	obj_create_reader(int fd, char *buffer, size_t buffer_size)
{
	return ((t_obj_reader){
		.fd = fd,
		.buffer = buffer,
		.buffer_size = buffer_size,
		.len = 0,
		.i = 0,
		.column = 0,
		.line = 1});
}

int16_t	obj_reader_peek(t_obj_reader *self)
{
	size_t	len;

	if (self->i >= self->len)
	{
		len = read(self->fd, self->buffer, self->buffer_size);
		if (len <= 0)
			return (len);
		self->i = 0;
		self->len = len;
	}
	return (self->buffer[self->i]);
}

int	obj_reader_next(t_obj_reader *self)
{
	int16_t	c;

	if ((c = obj_reader_peek(self)) == '\n')
	{
		self->line++;
		self->column = 0;
	}
	else if (c == -1)
		return (RIP_READ);
	else
		self->column++;
	self->i++;
	return (GET_RESULT);
}
