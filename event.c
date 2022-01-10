#include "scop.h"

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
					data->model.angle.x -= 0.1f;
					break;
				case SDLK_KP_6:
					data->model.angle.x += 0.1f;
					break;
				case SDLK_KP_8:
					data->model.angle.y += 0.1f;
					break;
				case SDLK_KP_2:
					data->model.angle.y -= 0.1f;
					break;
				case SDLK_KP_7:
					data->model.angle.z += 0.1f;
					break;
				case SDLK_KP_9:
					data->model.angle.z -= 0.1f;
					break;
				case SDLK_ESCAPE:
					return (0);
					break;
				case SDLK_s:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.dir, deltaTime * SPEED));
					break;
				case SDLK_w:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.dir, deltaTime * SPEED));
					break;
				case SDLK_a:
					data->camera.position = vec3_sub(data->camera.position, vec3_mult_value(data->camera.right, deltaTime * SPEED));
					break;
				case SDLK_d:
					data->camera.position = vec3_add(data->camera.position, vec3_mult_value(data->camera.right, deltaTime * SPEED));
					break;
				case SDLK_p:
				{
					data->ok.transition = 0;
					data->ok.showTexture = !data->ok.showTexture;
					break;
				}
				case SDLK_o:
					data->ok.test = !data->ok.test;
					break;
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