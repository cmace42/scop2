/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printMat4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:58 by cmace             #+#    #+#             */
/*   Updated: 2022/03/02 13:21:39 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	printMat4(t_mat4 mat)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			printf("%f ", mat.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}
