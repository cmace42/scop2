#include "scop.h"




void loop(t_env data)
{
	
	int running = 1;
	// glEnable(GL_CULL_FACE);
	// printf("Starting loop\n");
	// printf("size triangle to draw %ld\n", obj.vertex_size_data);
	data.ok.colorTest = 0;
	printf("========================%f\n", data.model.whl.x);	
	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		data.time = getDataTime(data.time);
		running = event(&data, data.time.deltaTime);
		applyPerspective(data.programId, &data.model, &data.camera);
		// premier tampon d'attributs : les sommets
		data.ok.ShowTextureLoc = glGetUniformLocation(data.programId, "showTexture");
		glUniform1i(data.ok.ShowTextureLoc, data.ok.showTexture);
		data.ok.testLoc = glGetUniformLocation(data.programId, "test");
		glUniform1i(data.ok.testLoc, data.ok.test);
		data.ok.colorTestLoc = glGetUniformLocation(data.programId, "colortest");
		glUniform1i(data.ok.colorTestLoc, data.ok.colorTest);
		data.ok.colorTest++;
		data.ok.bidouilleTestLoc = glGetUniformLocation(data.programId, "bidouille");
		data.ok.bidouilleTest.x = sinf((float)SDL_GetTicks()/1000.0f) / 2.0f;
		data.ok.bidouilleTest.y = cosf((float)SDL_GetTicks()/1000.0f) / 2.0f;
		data.ok.bidouilleTest.z = tanf((float)SDL_GetTicks()/1000.0f) / 2.0f;
		glUniform3f(data.ok.bidouilleTestLoc, data.ok.bidouilleTest.x, data.ok.bidouilleTest.y,data.ok.bidouilleTest.z);
		render(data);
		SDL_Delay(1000/60); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
	}
	glDeleteTextures(1, &data.texture);
	glDeleteProgram(data.programId);
	glDeleteVertexArrays(1, &data.vao.VertexArrayID);
	glDeleteBuffers(1, &data.vao.vertexBuffer);
	glDeleteBuffers(1, &data.vao.textureBuffer);
}