/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toRadian.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:23 by cmace             #+#    #+#             */
/*   Updated: 2022/03/02 13:21:39 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float	toRadian(float angle)
{
	return (angle * M_PI / 180.0);
}