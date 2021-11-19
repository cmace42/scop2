#include "scop.h"

void applyPerspective(GLuint programId, float xAngModel, float yAngModel)
{
	t_mat4 modelMatrice;
	t_mat4 mvpMatrice;
	t_vec3 cameraPos;
	t_vec3 cameraTarget;
	t_vec3 up;
	t_mat4 cameraMat;
	t_mat4 projectionMat;
	GLuint matrixId;

	modelMatrice = initModelMatrice(xAngModel, yAngModel);
	cameraPos = vec3_new(0.0f, 0.0f, 10.0f);
	cameraTarget = vec3_new(0.0f, 0.0f, 0.0f);
	up = vec3_new(0.0f, 1.0f, 5.0f);
	cameraMat = lookAt(cameraPos, cameraTarget, up);
	projectionMat = initPerspective(45.0f, 0.1f, 100.0f);
	mvpMatrice= mat4_mult(mat4_mult(projectionMat, cameraMat), modelMatrice);
	// Obtient un identifiant pour notre variable uniforme "MVP". 
	// Seulement au moment de l'initialisation. 
	matrixId = glGetUniformLocation(programId, "MVP"); 
	
	// Envoie notre transformation au shader actuel dans la variable uniforme "mvpMatrice" 
	// Pour chaque modèle affiché, comme la mvpMatrice sera différente (au moins pour la partie M)
	glUniformMatrix4fv(matrixId, 1, GL_TRUE, &mvpMatrice.m[0][0]);
}