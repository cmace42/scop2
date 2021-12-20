#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;


void loop(t_env data)
{
	int xMouse, yMouse;
	int running = 1;
	data.texture = loadBMP_custom("texturetest.bmp");
	data.programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
	// glEnable(GL_CULL_FACE);
	// printf("Starting loop\n");
	// printf("size triangle to draw %ld\n", obj.vertex_size_data);
	while(running)
	{
		data.time.currentTime = SDL_GetTicks();
		data.time.deltaTime = (float)(data.time.currentTime - data.time.lastTime);
		data.time.lastTime = data.time.currentTime;
		SDL_GetRelativeMouseState(&xMouse, &yMouse);
		data.camera.horizontalAngle += MOUSESPEED * data.time.deltaTime * (float)(xMouse);
		data.camera.verticalAngle += MOUSESPEED * data.time.deltaTime * (float)(yMouse);

		data.camera.dir = vec3_new(cosf(data.camera.verticalAngle) * sinf(data.camera.horizontalAngle),
				sinf(data.camera.verticalAngle),
				cosf(data.camera.verticalAngle) * cosf(data.camera.horizontalAngle));
		data.camera.right = vec3_new(sinf(data.camera.horizontalAngle - 3.14f/2.0f),
				0,
				cosf(data.camera.horizontalAngle - 3.14f/2.0f));
		data.camera.up = vec3_cross(data.camera.right, data.camera.dir);
		data.camera.target = vec3_add(data.camera.position, data.camera.dir);
		running = event(&data.model, &data.camera, data.time.deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// premier tampon d'attributs : les sommets
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
		// premier tampon d'attributs : les couleurs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, data.vao.vertexBuffer);
		glVertexAttribPointer(
		1,                  //cela correspond au « layout » dans le shader 
		3,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glUseProgram(data.programId);
		// printf("camera = x : %f, y : %f, z : %f\n\n",camera.position.x,camera.position.y,camera.position.z);
		applyPerspective(data.programId, data.model, data.camera);
		// // Dessine le triangle ! 
		glDrawArrays(GL_TRIANGLES, 0, data.modelData.vertex_size_data * 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		SDL_GL_SwapWindow(data.window);	
		SDL_Delay(1000/60); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
		//do some stuff
	}
	glDeleteTextures(1, &data.texture);
	glDeleteProgram(data.programId);
	glDeleteVertexArrays(1, &data.vao.VertexArrayID);
	glDeleteBuffers(1, &data.vao.vertexBuffer);
	glDeleteBuffers(1, &data.vao.textureBuffer);
}