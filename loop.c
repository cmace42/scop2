#include "scop.h"




void loop(t_env data)
{
	
	int running = 1;
	// glEnable(GL_CULL_FACE);
	// printf("Starting loop\n");
	// printf("size triangle to draw %ld\n", obj.vertex_size_data);
	data.ok.colorTest = 0;
	while(running)
	{
		data.time.currentTime = SDL_GetTicks();
		data.time.deltaTime = (float)(data.time.currentTime - data.time.lastTime);
		data.time.lastTime = data.time.currentTime;
		running = event(&data, data.time.deltaTime);
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
		data.ok.ShowTextureLoc = glGetUniformLocation(data.programId, "showTexture");
		glUniform1i(data.ok.ShowTextureLoc, data.ok.showTexture);
		data.ok.testLoc = glGetUniformLocation(data.programId, "test");
		glUniform1i(data.ok.testLoc, data.ok.test);
		data.ok.colorTestLoc = glGetUniformLocation(data.programId, "colortest");
		glUniform1i(data.ok.colorTestLoc, data.ok.colorTest);
		data.ok.colorTest++;
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
		// premier tampon d'attributs : les couleurs
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