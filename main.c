#include "scop.h"

int main(int argc, char **argv)
{
	t_env env;
	size_t i;
	int ret;

	if (argc != 2)
	{
		printf("fais l'usage\n");
		return (0);
	}
	if ((ret = init(&env, argv[1])) == GET_RESULT)
	{
		printf("%s", keymessage);
		loop(env);
	}
	if (ret != WRONG_CHAR && ret != RIP_READ && ret != RIP_OPEN && ret != NO_VERTEX)
		freeAll(&env);
	glDeleteTextures(1, &env.texture);
	glDeleteProgram(env.programId);
	i = 0;
	while (i < env.modelData.size_groupe)
	{
		glDeleteVertexArrays(1, &env.vao[i].VertexArrayID);
		glDeleteBuffers(1, &env.vao[i].vertexBuffer);
		glDeleteBuffers(1, &env.vao[i].textureBuffer);
		glDeleteBuffers(1, &env.vao[i].colorFacesBuffer);
		glDeleteBuffers(1, &env.vao[i].colorTrianglesBuffer);
		i++;
	}
	if (env.context)
		SDL_GL_DeleteContext(env.context);
	SDL_DestroyWindow(env.window);
	SDL_Quit();
}