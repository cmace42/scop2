#include "scop.h"

void render(t_env data)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, data.vao.vertexBuffer);
	glVertexAttribPointer(
	0,                  //cela correspond au « layout » dans le shader 
	3,                  // taille
	GL_FLOAT,           // type 
	GL_FALSE,           // normalisé ? 
	0,                  // nombre d'octets séparant deux sommets dans le tampon
	(void*)0            // décalage du tableau de tampon
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, data.vao.colorBuffer);
	glVertexAttribPointer(
	1,                  //cela correspond au « layout » dans le shader 
	3,                  // taille
	GL_FLOAT,           // type 
	GL_FALSE,           // normalisé ? 
	0,                  // nombre d'octets séparant deux sommets dans le tampon
	(void*)0            // décalage du tableau de tampon
	);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, data.vao.vertexBuffer);
	glVertexAttribPointer(
	2,                  //cela correspond au « layout » dans le shader 
	3,                  // taille
	GL_FLOAT,           // type 
	GL_FALSE,           // normalisé ? 
	0,                  // nombre d'octets séparant deux sommets dans le tampon
	(void*)0            // décalage du tableau de tampon
	);
	glUseProgram(data.programId);
	glDrawArrays(GL_TRIANGLES, 0, data.modelData.vertex_size_data * 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
	glDisableVertexAttribArray(0);
	SDL_GL_SwapWindow(data.window);
}