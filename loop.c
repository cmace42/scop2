#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;


void loop(t_vao vao, SDL_Window* window)
{
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
		5,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		// premier tampon d'attributs : les couleurs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vao.colorBuffer);
		glVertexAttribPointer(
		1,                  //cela correspond au « layout » dans le shader 
		5,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vao.vertexBuffer2);
		glVertexAttribPointer(
		0,                  //cela correspond au « layout » dans le shader 
		5,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		// premier tampon d'attributs : les couleurs
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, vao.colorBuffer2);
		glVertexAttribPointer(
		1,                  //cela correspond au « layout » dans le shader 
		5,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glUseProgram(programId);
		t_vec3 model1 = vec3_new(0, 0, 0);
		t_vec3 model2 = vec3_new(5, 5, 5);
		applyPerspective(programId, angleModel.x, angleModel.y, "MVP" , model1);
		applyPerspective(programId, angleModel.x, angleModel.y, "MVP2" ,model2);

		// // Dessine le triangle ! 
		glDrawArrays(GL_TRIANGLES, 3, 13 * 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		// glDisableVertexAttribArray(2);
		SDL_GL_SwapWindow(window); // Sans ca pas d'image ?
		SDL_Delay(17); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
		//do some stuff
	}
}