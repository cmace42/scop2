/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:37 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 11:42:05 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_time	getDataTime(t_time last)
{
	t_time	new;

	new.currentTime = SDL_GetTicks();
	new.deltaTime = (float)(new.currentTime - last.lastTime);
	new.lastTime = new.currentTime;
	return (new);
}
