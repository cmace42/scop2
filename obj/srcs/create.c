/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:10:41 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 15:19:27 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_vertex_array	create_vertex_array(size_t size)
{
	return ((t_vertex_array){
		.len = 0,
		.size = size,
		.this = (t_vertex *)malloc(sizeof(t_vertex) * size),
	});
}

t_uv_array	create_uv_array(size_t size)
{
	return ((t_uv_array){
		.len = 0,
		.size = size,
		.this = (t_uv *)malloc(sizeof(t_uv) * size),
	});
}

t_faces_array	create_triangle_array(size_t size)
{
	return ((t_faces_array){
		.len = 0,
		.size = size,
		.triangle = (t_triangle *)malloc(sizeof(t_triangle) * size),
	});
}

t_obj	create_groupe(size_t size, t_face_type type)
{
	return ((t_obj){
		.size = size,
		.type = type,
		.groupe = (t_groupe *)malloc(sizeof(t_groupe) * size),
	});
}

t_facesPerLine	create_fpl_array(size_t size)
{
	return ((t_facesPerLine){
		.size = size,
		.len = 0,
		.this = (size_t *)malloc(sizeof(size_t) * size),
	});
}
