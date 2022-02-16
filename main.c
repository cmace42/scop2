#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;

extern char skyboxvertexshader_glsl[];
extern int skyboxvertexshader_glsl_len;
extern char skyboxfragmentshader_glsl[];
extern int skyboxfragmentshader_glsl_len;

static char *faces[] = 
{
	"right.bmp",
	"left.bmp",
	"top.bmp",
	"bottom.bmp",
	"front.bmp",
	"back.bmp"
};

int main(int argc, char **argv)
{
	t_env env;
	if (argc != 2)
	{
		printf("fais l'usage\n");
		return (0);
	}
	if (getModel(argv[1], &env.modelData))
	{
		if ((env.window = initWindow()) != NULL)
		{
			SDL_SetRelativeMouseMode(true);
			env.context = SDL_GL_CreateContext(env.window);
			env.vao = initOpenGL(env.modelData);
			loadSkyBox(faces, &env.cubemapTexture);
			if (!(env.model = initModel(env.modelData)))
			{
				printf("merde\n");
				return (0);
			}
			t_vec3 whltotal = (t_vec3){0.0,0.0,0.0};
			size_t i = 0;
			while (i < env.modelData.size_groupe)
			{
				whltotal.x += fabs(env.model[i].whl.x);
				whltotal.y += fabs(env.model[i].whl.y);
				whltotal.z += fabs(env.model[i].whl.z);
				i++;
			}
			env.camera = initCamera(whltotal);
			loadBMP_custom("petit-poney.bmp", &env.bmp1);
			loadBMP_custom("diffuse.bmp", &env.bmp2);
			env.texture = getTextureId(env.bmp2);
			env.programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
			env.programSkyboxId = loadShaders(skyboxvertexshader_glsl, skyboxvertexshader_glsl_len, skyboxfragmentshader_glsl, skyboxfragmentshader_glsl_len);
			env.action.showTexture = false;
			env.action.test = false;
			env.action.transition = 1;
			env.action.rotate = true;
			env.action.rotateKeyboardMode = true;
			env.action.isBmp1 = false;
			env.action.haveSpeedBoost = false;
			env.action.showFace = 1;
			env.action.showDept = false;
			env.time.lastTime = 0;
			env.speed = fabs(env.model[0].whl.y) / 20.0f;
			loop(env);
			size_t y;
			y = 0;
			while (y < env.modelData.size_groupe)
			{
				if (env.modelData.vertex[y].buffer_data)
					free(env.modelData.vertex[y].buffer_data);
				if (env.modelData.uv[y].buffer_data)
					free(env.modelData.uv[y].buffer_data);
				if (env.modelData.normal[y].buffer_data)
					free(env.modelData.normal[y].buffer_data);
				if (env.modelData.color[y].buffer_data)
					free(env.modelData.color[y].buffer_data);
				if (env.modelData.vertex[y].name)
					free(env.modelData.vertex[y].name);
				y++;
			}
			if (env.bmp1.data)
				free(env.bmp1.data);
			if (env.bmp2.data)
				free(env.bmp2.data);
			if (env.model)
				free(env.model);
			if (env.modelData.color)
				free(env.modelData.color);
			if (env.modelData.vertex)
				free(env.modelData.vertex);
			if (env.modelData.uv)
				free(env.modelData.uv);
			if (env.modelData.normal)
				free(env.modelData.normal);
			if (env.vao)
				free(env.vao);
		}
		else
			printf("Failed to init window\n");
		if (env.context)
			SDL_GL_DeleteContext(env.context);
		SDL_DestroyWindow(env.window);
		SDL_Quit();
	}
	// 	if ((ret = loadObj(argv[1], &env.modelData, &env.model.whl)) != GET_RESULT)
	// 	{
	// 		printf("num de l'erreur = %d", ret);
	// 		if (env.modelData.vertex_buffer_data)
	// 			free(env.modelData.vertex_buffer_data);
	// 		return(1);
	// 	}
	// 	else 
	// 	{
	// 		if ((env.window = initWindow()) != NULL)
	// 		{
	// 			SDL_SetRelativeMouseMode(true);
	// 			env.context = SDL_GL_CreateContext(env.window);
	// 			env.vao = initOpenGL(env.modelData);
	// 			free(env.modelData.vertex_buffer_data);
	// 			env.camera = initCamera();
	// 			env.model = initModel(env.model.whl);
	// 			loadBMP_custom("petit-poney.bmp", &env.bmp1);
	// 			loadBMP_custom("texturetest.bmp", &env.bmp2);
	// 			env.texture = getTextureId(env.bmp2);
	// 			env.programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
	// 			env.action.showTexture = false;
	// 			env.action.test = false;
	// 			env.action.transition = 1;
	// 			env.action.rotate = true;
	// 			env.action.rotateKeyboardMode = true;
	// 			env.action.isBmp1 = false;
	// 			env.action.haveSpeedBoost = false;
	// 			env.time.lastTime = 0;
	// 			loop(env);
	// 			if (env.modelData.uv_static_buffer_data)
	// 			{
	// 				free(env.modelData.uv_static_buffer_data);
	// 			}
	// 			if (env.modelData.normal_buffer_data)
	// 				free(env.modelData.normal_buffer_data);
	// 			if (env.modelData.uv_buffer_data)
	// 				free(env.modelData.uv_buffer_data);
	// 			if (env.modelData.color_buffer_data)
	// 				free(env.modelData.color_buffer_data);
	// 			if (env.bmp1.data)
	// 				free(env.bmp1.data);
	// 			if (env.bmp2.data)
	// 				free(env.bmp2.data);
	// 		}
	// 		else
	// 			printf("Failed to init window\n");
	// 		if (env.context)
	// 			SDL_GL_DeleteContext(env.context);
	// 		SDL_DestroyWindow(env.window);
	// 		SDL_Quit();
	// 	}
}