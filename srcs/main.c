/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:42 by cmace             #+#    #+#             */
/*   Updated: 2022/03/07 10:18:01 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	main(int argc, char **argv)
{
	t_env	env;
	size_t	i;
	int		ret;

	if (argc < 2)
	{
		printf("fais l'usage\n");
		return (0);
	}
	printf("%d\n",argc);
	if ((ret = init(&env, argv[1], argc == 3 ? argv[2] : NULL)) == GET_RESULT)
	{
		printf("%s", KEYMESSAGE);
		loop(env);
	}
	if (ret != WRONG_CHAR && ret != RIP_READ && ret != RIP_OPEN && ret != NO_VERTEX)
		freeAll(&env, ret);
	glDeleteTextures(1, &env.texture);
	glDeleteProgram(env.programId);
	i = 0;
	while (i < env.modelData.size_groupe)
	{
		glDeleteVertexArrays(1, &env.vao[i].VertexArrayID);
		glDeleteBuffers(1, &env.vao[i].vertexBuffer);
		glDeleteBuffers(1, &env.vao[i].textureBuffer);
		glDeleteBuffers(1, &env.vao[i].colorFacesBuffer);
		glDeleteBuffers(1, &env.vao[i].colorTrianglesBuffer);
		i++;
	}
	if (env.context)
		SDL_GL_DeleteContext(env.context);
	SDL_DestroyWindow(env.window);
	SDL_Quit();
}
