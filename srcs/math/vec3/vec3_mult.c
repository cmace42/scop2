/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:07:50 by cmace             #+#    #+#             */
/*   Updated: 2022/03/02 13:21:39 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.x * b.x,
		a.y * b.y,
		a.z * b.z});
}

t_vec3	vec3_mult_value(t_vec3 a, float value)
{
	return ((t_vec3){
		a.x * value,
		a.y * value,
		a.z * value});
}