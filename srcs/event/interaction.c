/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:56 by cmace             #+#    #+#             */
/*   Updated: 2022/03/02 13:21:39 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_action	interact(t_env data)
{
	t_vec3	colorInc;
	float	tmp;

	tmp = ((float)SDL_GetTicks() / 1000.0f) / M_PI;
	colorInc = data.action.autoColor ? (t_vec3){
		.x = tmp,
		.y = tmp,
		.z = tmp,
	} : (t_vec3){
		.x = data.action.colorInc.x / M_PI,
		.y = data.action.colorInc.y / M_PI,
		.z = data.action.colorInc.z / M_PI,
	};
	data.action.ShowTextureLoc = glGetUniformLocation(data.programId, "showTexture");
	glUniform1i(data.action.ShowTextureLoc, data.action.showTexture);
	data.action.autoColorLoc = glGetUniformLocation(data.programId, "autoColorMode");
	glUniform1i(data.action.autoColorLoc, data.action.autoColor);
	data.action.transition += data.time.deltaTime / 2000;
	data.action.transition = (data.action.transition > 1) ? 1 : data.action.transition;
	data.action.transitionLoc = glGetUniformLocation(data.programId, "transition");
	glUniform1f(data.action.transitionLoc, data.action.transition);
	data.action.colorLoc = glGetUniformLocation(data.programId, "colorMode");
	data.action.color.x = (cosf(colorInc.x * 2) + 1) / 2.0f;
	data.action.color.y = (cosf(colorInc.y * 3) + 1) / 2.0f;
	data.action.color.z = (cos(colorInc.z * 5) + 1) / 2.0f;
	glUniform3f(data.action.colorLoc, data.action.color.x, data.action.color.y, data.action.color.z);
	data.action.greymodeLoc = glGetUniformLocation(data.programId, "greymode");
	glUniform1i(data.action.greymodeLoc, data.action.greymode);
	return (data.action);
}
