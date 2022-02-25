#include "scop.h"

int eventTemp()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return(0);
		switch (event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				return (0);
				break;
		}
	}
	return (1);
}

void doRotate(t_objectInWorld **model, t_vec3 rotate, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		(*model)[i].angle = vec3_add((*model)[i].angle, rotate);
		i++;
	}
}

void doTranslate(t_objectInWorld **model, t_vec3 translate, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		(*model)[i].position = vec3_add((*model)[i].position, translate);
		i++;
	}
}

int event(t_env *data, float deltaTime)
{
	
	SDL_Event event;
	int xMouse, yMouse;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return(0);
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_KP_4:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.y = 0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.x = 0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_KP_6:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.y = -0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.x = -0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_KP_8:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.x= -0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.y = 0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_KP_2:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.x= 0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.y = -0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_KP_7:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.z = 0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.z = 0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_KP_9:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.z = -0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.z = -0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_ESCAPE:
					return (0);
					break;
				case SDLK_s:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.dir, deltaTime * (SPEED + (data->speed * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_w:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.dir, deltaTime * (SPEED + (data->speed * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_a:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.right, deltaTime * (SPEED + (data->speed * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_d:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.right, deltaTime * (SPEED + (data->speed * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_SPACE:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.up, deltaTime * (SPEED + (data->speed * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_LCTRL:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.up, deltaTime * (SPEED + (data->speed * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_p:
				{
					data->action.transition = 0;
					data->action.showTexture = !data->action.showTexture;
					break;
				}
				case SDLK_o:
					data->action.autoColor = !data->action.autoColor;
					break;
				case SDLK_r:
				{
					data->action.rotate = !data->action.rotate;
					break;
				}
				case SDLK_l:
				{
					data->action.rotateKeyboardMode = !data->action.rotateKeyboardMode;
					break;
				}
				case SDLK_m:
				{
					data->action.isBmp1 = !data->action.isBmp1;
					glDeleteTextures(1, &data->texture);
					if (data->action.isBmp1)
						data->texture = getTextureId(data->bmp1);
					else
						data->texture = getTextureId(data->bmp2);
					break;
				}
				case SDLK_LSHIFT:
				{
					data->action.haveSpeedBoost = true;
					break;
				}
				case SDLK_DELETE:
				{
					if (data->action.showFace == 0)
					{
						data->action.showFace = 1;
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					}
					else if (data->action.showFace == 1)
					{
						data->action.showFace = 2;
						glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
					}
					else if (data->action.showFace == 2)
					{
						data->action.showFace = 0;
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					}
					break;
				}
				case SDLK_PAGEUP:
				{
					data->action.showDept = !data->action.showDept;
					if (!data->action.showDept)
						glEnable(GL_DEPTH_TEST);
					else
						glDisable(GL_DEPTH_TEST);
					break;
				}
				case SDLK_i:
				{
					data->action.isFacesColor = !data->action.isFacesColor;
					break;
				}
				case SDLK_u:
				{
					data->action.greymode = !data->action.greymode;
					break;
				}
				case SDLK_k:
				{
					data->action.glcullface = !data->action.glcullface;
					if (data->action.glcullface)
						glEnable(GL_CULL_FACE);
					else
						glDisable(GL_CULL_FACE);
					break;
				}
				case SDLK_z:
				{
					if (!data->action.greymode)
						data->action.colorInc.x+= 0.02;
					break;
				}
				case SDLK_x:
				{
					if (!data->action.greymode)
						data->action.colorInc.y+= 0.02;
					break;
				}
				case SDLK_c:
				{
					if (!data->action.greymode)
						data->action.colorInc.z+= 0.02;
					break;
				}
				case SDLK_t:
				{
					data->action.colorInc = (t_vec3){0.0f,0.0f,0.0f};
					break;
				}
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_LSHIFT:
				{
					data->action.haveSpeedBoost = false;
					break;
				}
			}
		}
	}
	mouseCamera(&data->camera, &xMouse, &yMouse, data->time.deltaTime);
	return (1);
}