#include "scop.h"

int main(int argc, char **argv)
{
	t_info info;
	GLuint vertexBuffer;

	if (initWindow(info.window, info.context) == true)
	{
		vertexBuffer = initOpenGL();
		loop(vertexBuffer);
		//do some stuff
	}
	else
	{
		printf("Failed to init window\n");
		SDL_GL_DeleteContext(info.context);
		SDL_DestroyWindow(info.window);
		SDL_Quit();
	}
}