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
					{
						doRotate(&data->model, (t_vec3){.y = 0.1f}, data->modelData.size_groupe);
					}
					else
					{
						doTranslate(&data->model, (t_vec3){.x = 0.1f}, data->modelData.size_groupe);
					}
					break;
				}
				case SDLK_KP_6:
				{
					if (data->action.rotateKeyboardMode)
					{
						doRotate(&data->model, (t_vec3){.y = -0.1f}, data->modelData.size_groupe);
					}
					else
					{
						doTranslate(&data->model, (t_vec3){.x = -0.1f}, data->modelData.size_groupe);
					}
					break;
				}
				case SDLK_KP_8:
				{
					if (data->action.rotateKeyboardMode)
					{
						doRotate(&data->model, (t_vec3){.x= -0.1f}, data->modelData.size_groupe);
					}
					else
					{
						doTranslate(&data->model, (t_vec3){.y = 0.1f}, data->modelData.size_groupe);
					}
					break;
				}
				case SDLK_KP_2:
				{
					if (data->action.rotateKeyboardMode)
					{
						doRotate(&data->model, (t_vec3){.x= 0.1f}, data->modelData.size_groupe);
					}
					else
					{
						doTranslate(&data->model, (t_vec3){.y = -0.1f}, data->modelData.size_groupe);
					}
					break;
				}
				case SDLK_KP_7:
				{
					if (data->action.rotateKeyboardMode)
					{
						doRotate(&data->model, (t_vec3){.z= 0.1f}, data->modelData.size_groupe);
					}
					else
						doTranslate(&data->model, (t_vec3){.z = 0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_KP_9:
				{
					if (data->action.rotateKeyboardMode)
						doRotate(&data->model, (t_vec3){.z= -0.1f}, data->modelData.size_groupe);
					else
						doTranslate(&data->model, (t_vec3){.z = -0.1f}, data->modelData.size_groupe);
					break;
				}
				case SDLK_ESCAPE:
					return (0);
					break;
				case SDLK_s:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.dir, deltaTime * (SPEED + (SPEEDBOOST * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_w:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.dir, deltaTime * (SPEED + (SPEEDBOOST * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_a:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.right, deltaTime * (SPEED + (SPEEDBOOST * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_d:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.right, deltaTime * (SPEED + (SPEEDBOOST * (float)data->action.haveSpeedBoost))));
					break;
				case SDLK_SPACE:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.up, deltaTime * SPEED));
					break;
				case SDLK_LCTRL:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.up, deltaTime * SPEED));
					break;
				case SDLK_p:
				{
					data->action.transition = 0;
					data->action.showTexture = !data->action.showTexture;
					break;
				}
				case SDLK_o:
					data->action.test = !data->action.test;
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
					{
						data->texture = getTextureId(data->bmp1);
					}
					else
					{
						data->texture = getTextureId(data->bmp2);
					}
					break;
				}
				case SDLK_LSHIFT:
				{
					data->action.haveSpeedBoost = true;
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
	SDL_GetRelativeMouseState(&xMouse, &yMouse);
	data->camera.angle.x += MOUSESPEED * deltaTime * (float)(xMouse);
	data->camera.angle.y += MOUSESPEED * deltaTime * (float)(yMouse);
	data->camera.dir = vec3_new(cosf(data->camera.angle.y) * sinf(data->camera.angle.x),
			sinf(data->camera.angle.y),
			cosf(data->camera.angle.y) * cosf(data->camera.angle.x));
	data->camera.right = vec3_new(sinf(data->camera.angle.x - 3.14f/2.0f),
			0,
			cosf(data->camera.angle.x - 3.14f/2.0f));
	data->camera.up = vec3_cross(data->camera.right, data->camera.dir);
	data->camera.target = vec3_add(data->camera.position, data->camera.dir);
	// printf("%f, %f, %f\n", right.x, right.y, right.z);
	// printf("data->camera = x : %f, y : %f, z : %f\n\n",data->camera.position.x,data->camera.position.y,data->camera.position.z);

	return (1);
}