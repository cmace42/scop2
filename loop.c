#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;


void loop(GLuint vertexBuffer)
{
	GLuint programID = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);

	while(event())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// premier tampon d'attributs : les sommets
		glEnableVertexAttribArray(0); 
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); 
		glVertexAttribPointer( 
		0,                  // attribut 0. Aucune raison particulière pour 0, mais cela doit correspondre au « layout » dans le shader 
		3,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		); 
		glUseProgram(programID);
		// // Dessine le triangle ! 
		glDrawArrays(GL_TRIANGLES, 0, 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		SDL_Delay(17); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
		//do some stuff
	}
}