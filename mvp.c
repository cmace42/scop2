#include "scop.h"

void applyPerspective(GLuint programId, t_objectInWorld model, t_objectInWorld camera)
{
	t_mat4 modelMatrice;
	t_mat4 mvpMatrice;
	t_mat4 cameraMat;
	t_mat4 projectionMat;
	GLuint matrixId;

	modelMatrice = initModelMatrice(model.horizontalAngle, model.verticalAngle);
	cameraMat = lookAt(camera.position, camera.target, camera.up);
	projectionMat = initPerspective(45.0f, 0.1f, 100.0f);
	mvpMatrice= mat4_mult(mat4_mult(projectionMat, cameraMat), modelMatrice);
	// Obtient un identifiant pour notre variable uniforme "MVP". 
	// Seulement au moment de l'initialisation. 
	matrixId = glGetUniformLocation(programId, "MVP"); 
	
	// Envoie notre transformation au shader actuel dans la variable uniforme "mvpMatrice" 
	// Pour chaque modèle affiché, comme la mvpMatrice sera différente (au moins pour la partie M)
	glUniformMatrix4fv(matrixId, 1, GL_TRUE, &mvpMatrice.m[0][0]);
}