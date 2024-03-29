/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_scaling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:28 by cmace             #+#    #+#             */
/*   Updated: 2022/03/02 13:21:39 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	mat4_scaling(t_vec3 scale)
{
	return ((t_mat4){
		.m ={
			{scale.x, 0.0, 0.0, 0.0},
			{0.0, scale.y, 0.0, 0.0},
			{0.0, 0.0, scale.z, 0.0},
			{0.0, 0.0, 0.0, 1.0}
		}});
}