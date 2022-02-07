#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;

int main(int argc, char **argv)
{
	t_env env;
	if (argc != 2)
	{
		printf("fais l'usage\n");
		return (0);
	}
	if (!getModel(argv[1], &env.modelData))
	{
		return (0);
	}
		// if (ret == GET_RESULT)
		// 	printobj(obj);
		// if ((ret = loadObj(argv[1], &env.modelData, &env.model.whl)) != GET_RESULT)
		// {
		// 	printf("num de l'erreur = %d", ret);
		// 	if (env.modelData.vertex_buffer_data)
		// 		free(env.modelData.vertex_buffer_data);
		// 	return(1);
		// }
		// else 
		// {
		// 	if ((env.window = initWindow()) != NULL)
		// 	{
		// 		SDL_SetRelativeMouseMode(true);
		// 		env.context = SDL_GL_CreateContext(env.window);
		// 		env.vao = initOpenGL(env.modelData);
		// 		free(env.modelData.vertex_buffer_data);
		// 		env.camera = initCamera();
		// 		env.model = initModel(env.model.whl);
		// 		loadBMP_custom("petit-poney.bmp", &env.bmp1);
		// 		loadBMP_custom("texturetest.bmp", &env.bmp2);
		// 		env.texture = getTextureId(env.bmp2);
		// 		env.programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
		// 		env.action.showTexture = false;
		// 		env.action.test = false;
		// 		env.action.transition = 1;
		// 		env.action.rotate = true;
		// 		env.action.rotateKeyboardMode = true;
		// 		env.action.isBmp1 = false;
		// 		env.action.haveSpeedBoost = false;
		// 		env.time.lastTime = 0;
		// 		loop(env);
		// 		if (env.modelData.uv_static_buffer_data)
		// 		{
		// 			free(env.modelData.uv_static_buffer_data);
		// 		}
		// 		if (env.modelData.normal_buffer_data)
		// 			free(env.modelData.normal_buffer_data);
		// 		if (env.modelData.uv_buffer_data)
		// 			free(env.modelData.uv_buffer_data);
		// 		if (env.modelData.color_buffer_data)
		// 			free(env.modelData.color_buffer_data);
		// 		if (env.bmp1.data)
		// 			free(env.bmp1.data);
		// 		if (env.bmp2.data)
		// 			free(env.bmp2.data);
		// 	}
		// 	else
		// 		printf("Failed to init window\n");
		// 	if (env.context)
		// 		SDL_GL_DeleteContext(env.context);
		// 	SDL_DestroyWindow(env.window);
		// 	SDL_Quit();
		// }
}