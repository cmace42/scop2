/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:55 by cmace             #+#    #+#             */
/*   Updated: 2022/03/02 13:21:39 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	render(t_env data)
{
	size_t	i;

	i = 0;
	while (i < data.modelData.size_groupe)
	{
		glUseProgram(data.programId);
		applyPerspective(data.programId, &data.model[i], &data.camera);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, data.vao[i].vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, data.action.isFacesColor ? data.vao[i].colorFacesBuffer : data.vao[i].colorTrianglesBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, data.vao[i].textureBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glUseProgram(data.programId);
		glDrawArrays(GL_TRIANGLES, 0, data.modelData.vertex[i].size_data);
		glDisableVertexAttribArray(0);
		i++;
	}
	SDL_GL_SwapWindow(data.window);
}
