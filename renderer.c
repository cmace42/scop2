#include "scop.h"

void render(t_env data)
{
	size_t i;
	i = 0;

t_mat4 mvpMatrice;
	GLuint matrixId;
	t_mat4 projectionMat;
	// float scale = 1 / tan(INITIALFOV * 0.5 * M_PI / 180) * 2; 
    // projectionMat.m[0][0] = scale; // scale the x coordinates of the projected point 
    // projectionMat.m[1][1] = scale; // scale the y coordinates of the projected point 
	// projectionMat.m[2][2] = -MAXDIST / (MAXDIST - 0.1f); // used to remap z to [0,1] 
    // projectionMat.m[3][2] = -MAXDIST * 0.1f / (MAXDIST - 0.1f); // used to remap z [0,1] 
    // projectionMat.m[2][3] = -1; // set w = -z 
    // projectionMat.m[3][3] = 0;
	projectionMat = initPerspective(INITIALFOV, 0.1f, 1000);
	mvpMatrice = mat4_mult(projectionMat, data.camera.this);
	// mvpMatrice = mat4_identity();
	matrixId = glGetUniformLocation(data.programSkyboxId, "MVP");

	// Envoie notre transformation au shader actuel dans la variable uniforme "mvpMatrice" 
	// Pour chaque modèle affiché, comme la mvpMatrice sera différente (au moins pour la partie M)
	glUniformMatrix4fv(matrixId, 1, GL_TRUE, &mvpMatrice.m[0][0]);
	glUseProgram(data.programSkyboxId);
	glBindVertexArray(data.vao[0].skyboxVAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, data.vao[0].skyboxVAO);
	glVertexAttribPointer(
	0,                  //cela correspond au « layout » dans le shader 
	3,                  // taille
	GL_FLOAT,           // type 
	GL_FALSE,           // normalisé ? 
	0,                  // nombre d'octets séparant deux sommets dans le tampon
	(void*)0            // décalage du tableau de tampon
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, data.cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	while (i < data.modelData.size_groupe)
	{
		glUseProgram(data.programId);
		applyPerspective(data.programId, &data.model[i], &data.camera);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, data.vao[i].vertexBuffer);
		glVertexAttribPointer(
		0,                  //cela correspond au « layout » dans le shader 
		3,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, data.action.isFacesColor ? data.vao[i].colorFacesBuffer : data.vao[i].colorTrianglesBuffer);
		glVertexAttribPointer(
		1,                  //cela correspond au « layout » dans le shader 
		3,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, data.vao[i].textureBuffer);
		glVertexAttribPointer(
		2,                  //cela correspond au « layout » dans le shader 
		2,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glDrawArrays(GL_TRIANGLES, 0, data.modelData.vertex[i].size_data); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		i++;
	}
	

	SDL_GL_SwapWindow(data.window);
}