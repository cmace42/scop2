#include "scop.h"

t_action interact(t_env data)
{
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
	return (data.action);
}