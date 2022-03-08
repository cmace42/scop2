/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:10:26 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 15:15:10 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

int	obj_skip_nl(t_obj_reader *self)
{
	int16_t	c;
	int		ret;

	ret = GET_RESULT;
	while ((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		if ((ret = obj_reader_next(self)) != GET_RESULT)
			return (ret);
	}
	if (c <= -1)
		return (RIP_READ);
	return (ret);
}

int	obj_skip_whitespace(t_obj_reader *self)
{
	int16_t	c;
	int		ret;

	ret = GET_RESULT;
	while ((c = obj_reader_peek(self)) == ' ' || c == '\t' || c == '\r')
	{
		if ((ret = obj_reader_next(self)) != GET_RESULT)
			return (ret);
	}
	if (c <= -1)
		return (RIP_READ);
	return (ret);
}

void	printobj(t_obj obj)
{
	size_t	i;
	size_t	y;

	y = 0;
	i = 0;
	printf("%d\n", obj.type);
	printf("v.len : %zu, uv.len %zu, vn.len : %zu, faces.len : %zu\n", obj.vertex.len, obj.vt.len, obj.vn.len, obj.groupe[y].faces.len);
	if (obj.vertex.len > 0)
	{
		printf("Vertex %zu: \n\n", obj.vertex.len);
		while (i < obj.vertex.len)
		{
			printf("ligne %zu : %f %f %f\n", i, obj.vertex.this[i].x, obj.vertex.this[i].y, obj.vertex.this[i].z);
			i++;
		}
	}
	if (obj.vt.len > 0)
	{
		printf("Uv %zu: \n\n", obj.vt.len);
		i = 0;
		while (i < obj.vt.len)
		{
			printf("ligne %zu : %f %f %f\n", i, obj.vt.this[i].u, obj.vt.this[i].v, obj.vt.this[i].w);
			i++;
		}
	}
	if (obj.vn.len > 0)
	{
		printf("Normal %zu: \n\n", obj.vn.len);
		i = 0;
		while (i < obj.vn.len)
		{
			printf("ligne %zu : %f %f %f\n", i, obj.vn.this[i].x, obj.vn.this[i].y, obj.vn.this[i].z);
			i++;
		}
	}
	while (y < obj.len)
	{
		printf("%s len : %zu\n", obj.groupe[y].name, obj.groupe[y].faces.len);
		i = 0;
		if (obj.groupe[y].faces.len > 0)
		{
			printf("\nType : %d	Faces : %zu\n\n", obj.type, obj.groupe[y].faces.len);
			i = 0;
			while (i < obj.groupe[y].faces.len)
			{
				printf("ligne %zu : Vertex : %zu %zu %zu\n", i, obj.groupe[y].faces.triangle[i].a.indexVertex, obj.groupe[y].faces.triangle[i].b.indexVertex, obj.groupe[y].faces.triangle[i].c.indexVertex);
				i++;
			}
			i = 0;
			if (obj.type == Obj_Texture_Type || obj.type == Obj_Vertex_Texture_Normal_Type)
				while (i < obj.groupe[y].faces.len)
				{
					printf("ligne %zu : UV : %zu %zu %zu\n", i, obj.groupe[y].faces.triangle[i].a.indexUv, obj.groupe[y].faces.triangle[i].b.indexUv, obj.groupe[y].faces.triangle[i].c.indexUv);
					i++;
				}
			i = 0;
			if (obj.type == Obj_Normal_Type || obj.type == Obj_Vertex_Texture_Normal_Type)
				while (i < obj.groupe[y].faces.len)
				{
					printf("ligne %zu : Normal : %zu %zu %zu\n", i, obj.groupe[y].faces.triangle[i].a.indexNormal, obj.groupe[y].faces.triangle[i].b.indexNormal, obj.groupe[y].faces.triangle[i].c.indexNormal);
					i++;
				}
		}
		y++;
	}
	printf("%zu\n", obj.len);
}
