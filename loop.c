#include "scop.h"

void loop(t_env data)
{
	
	int running = 1;
	// glEnable(GL_CULL_FACE);
	// printf("Starting loop\n");
	// printf("size triangle to draw %ld\n", obj.vertex_size_data);
	data.action.colorTest = 0;
	data.action.transition = 1.0f;
	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		data.time = getDataTime(data.time);
		if (data.action.rotate)
		{
			data.model.angle.y += 0.02f;
		}
		running = event(&data, data.time.deltaTime);
		applyPerspective(data.programId, &data.model, &data.camera);
		data.action.ShowTextureLoc = glGetUniformLocation(data.programId, "showTexture");
		glUniform1i(data.action.ShowTextureLoc, data.action.showTexture);
		data.action.testLoc = glGetUniformLocation(data.programId, "test");
		glUniform1i(data.action.testLoc, data.action.test);
		data.action.colorTestLoc = glGetUniformLocation(data.programId, "colortest");
		glUniform1i(data.action.colorTestLoc, data.action.colorTest);
		data.action.transition += data.time.deltaTime / 2000;
		data.action.transition = (data.action.transition > 1) ? 1 : data.action.transition;
		data.action.transitionLoc = glGetUniformLocation(data.programId, "transition");
		glUniform1f(data.action.transitionLoc, data.action.transition);
		data.action.colorTest++;
		data.action.bidouilleTestLoc = glGetUniformLocation(data.programId, "bidouille");
		data.action.bidouilleTest.x = sinf((float)SDL_GetTicks()/1000.0f) / 2.0f;
		data.action.bidouilleTest.y = cosf((float)SDL_GetTicks()/1000.0f) / 2.0f;
		data.action.bidouilleTest.z = tanf((float)SDL_GetTicks()/1000.0f) / 2.0f;
		glUniform3f(data.action.bidouilleTestLoc, data.action.bidouilleTest.x, data.action.bidouilleTest.y,data.action.bidouilleTest.z);
		render(data);
		SDL_Delay(1000/80); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
	}
	glDeleteTextures(1, &data.texture);
	glDeleteProgram(data.programId);
	glDeleteVertexArrays(1, &data.vao.VertexArrayID);
	glDeleteBuffers(1, &data.vao.vertexBuffer);
	glDeleteBuffers(1, &data.vao.textureBuffer);
}