/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:13 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 16:43:33 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/scop.h"

void	applyPerspective(GLuint programId, t_objectInWorld *model, t_objectInWorld *camera)
{
	t_mat4	mvpMatrice;
	t_mat4	projectionMat;
	GLuint	matrixId;

	model->this = initModelMatrice(model->angle, model->whl, model->position);
	camera->this = lookAt(camera->position, camera->target, camera->up);
	projectionMat = initPerspective(INITIALFOV, 0.1f, MAXDIST);
	mvpMatrice = mat4_mult(mat4_mult(projectionMat, camera->this), model->this);
	matrixId = glGetUniformLocation(programId, "MVP");
	glUniformMatrix4fv(matrixId, 1, GL_TRUE, &mvpMatrice.m[0][0]);
}
