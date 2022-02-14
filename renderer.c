#include "scop.h"

void render(t_env data)
{
	size_t i;

	i = 0;
	while (i < data.modelData.size_groupe)
	{
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
		glBindBuffer(GL_ARRAY_BUFFER, data.vao[i].colorBuffer);
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
		glUseProgram(data.programId);
		glDrawArrays(GL_TRIANGLES, 0, data.modelData.vertex[i].size_data); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		i++;
	}
		SDL_GL_SwapWindow(data.window);
}