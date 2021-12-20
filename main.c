#include "scop.h"

int main(int argc, char **argv)
{
	t_env env;
	int ret;
	if (argc == 2)
	{
		if ((ret = loadObj(argv[1], &env.modelData)) != GET_RESULT)
		{
			printf("num de l'erreur = %d", ret);
			if (env.modelData.vertex_buffer_data)
				free(env.modelData.vertex_buffer_data);
			return(1);
		}
		else 
		{
			if ((env.window = initWindow()) != NULL)
			{
				SDL_SetRelativeMouseMode(true);
				env.context = SDL_GL_CreateContext(env.window);
				printf("%ld\n", env.modelData.uv_static_size_data);
				env.vao = initOpenGL(env.modelData);
				free(env.modelData.vertex_buffer_data);
				env.camera = initCamera();
				env.model = initModel();
				loop(env);
				if (env.modelData.uv_static_buffer_data)
				{
					free(env.modelData.uv_static_buffer_data);
				}
				if (env.modelData.normal_buffer_data)
					free(env.modelData.normal_buffer_data);
				//do some stuff
			}
			else
				printf("Failed to init window\n");
			if (env.context)
				SDL_GL_DeleteContext(env.context);
			SDL_DestroyWindow(env.window);
			SDL_Quit();
		}
	}
}