#include "scop.h"

int main(int argc, char **argv)
{
	t_info info;
	t_vao vao;
	t_model obj;
	GLfloat *vertexBufferData;

	if (argc == 2)
	{
		obj = loadObj(argv[1]);
		if ((info.window = initWindow()) != NULL)
		{
			SDL_SetRelativeMouseMode(true);
			info.context = SDL_GL_CreateContext(info.window);
			glViewport(0,0, WIDTH,HEIGHT);
			vao = initOpenGL(obj);
			free(obj.vertex_buffer_data);
			loop(vao, info.window, obj);
			//do some stuff
		}
		else
			printf("Failed to init window\n");
		if (info.context)
			SDL_GL_DeleteContext(info.context);
		SDL_DestroyWindow(info.window);
		SDL_Quit();
	}
}