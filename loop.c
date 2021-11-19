#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;


void loop(t_vao vao, SDL_Window* window)
{
	GLuint Texture = loadBMP_custom("texturetest.bmp");
	GLuint programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
	t_vec2 angleModel;

	angleModel.x = 0;
	angleModel.y = 0;

	while(event(&angleModel))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// premier tampon d'attributs : les sommets
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vao.vertexBuffer);
		glVertexAttribPointer(
		0,                  //cela correspond au « layout » dans le shader 
		3,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		// premier tampon d'attributs : les couleurs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vao.textureBuffer);
		glVertexAttribPointer(
		1,                  //cela correspond au « layout » dans le shader 
		2,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glUseProgram(programId);
		applyPerspective(programId, angleModel.x, angleModel.y);
		
		// // Dessine le triangle ! 
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		SDL_GL_SwapWindow(window); // Sans ca pas d'image ?
		SDL_Delay(17); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
		//do some stuff
	}
}