#include "scop.h"

int main(int argc, char **argv)
{
	t_info info;
	t_vao vao;
	t_model obj;

	if (argc != 2)
		return (0);
	else
	{
		loadObj(&obj, argv[1]);
		return (1);
	}
	if ((info.window = initWindow()) != NULL)
	{
		SDL_SetRelativeMouseMode(true);
		info.context = SDL_GL_CreateContext(info.window);
		vao = initOpenGL();
		loop(vao, info.window);
		//do some stuff
	}
	else
		printf("Failed to init window\n");
	if (info.context)
		SDL_GL_DeleteContext(info.context);
	SDL_DestroyWindow(info.window);
	SDL_Quit();
}