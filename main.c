#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;
extern char vertexshader2_glsl[];
extern int vertexshader2_glsl_len;
extern char fragmentshader2_glsl[];
extern int fragmentshader2_glsl_len;

int main(int argc, char **argv)
{
	t_env env;
	int ret;
	if (argc == 2)
	{
		if ((ret = loadObj(argv[1], &env.modelData, &env.model.whl)) != GET_RESULT)
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
				env.vao = initOpenGL(env.modelData);
				free(env.modelData.vertex_buffer_data);
				env.camera = initCamera();
				env.model = initModel(env.model.whl);
				env.texture = loadBMP_custom("texturetest.bmp");
				env.programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
				env.ok.showTexture = true;
				env.ok.test = false;
				env.ok.transition = 1;
				env.time.lastTime = 0;
				loop(env);
				if (env.modelData.uv_static_buffer_data)
				{
					free(env.modelData.uv_static_buffer_data);
				}
				if (env.modelData.normal_buffer_data)
					free(env.modelData.normal_buffer_data);
				if (env.modelData.normal_buffer_data)
					free(env.modelData.normal_buffer_data);
				if (env.modelData.uv_buffer_data)
					free(env.modelData.uv_buffer_data);
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