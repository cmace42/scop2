/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:44 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 16:43:33 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/scop.h"

void	loop(t_env data)
{
	int	running;

	running = 1;
	data.action.transition = 1.0f;
	while (running)
	{
		running = event(&data, data.time.deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		data.time = getDataTime(data.time);
		if (data.action.rotate)
			doRotate(&data.model, (t_vec3){.y = 0.02f}, data.modelData.size_groupe);
		data.action = interact(data);
		render(data);
		SDL_Delay(1000 / 60);
	}
}
