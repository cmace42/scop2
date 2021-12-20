#include "scop.h"

int event(t_objectInWorld *model, t_objectInWorld *camera, float deltaTime)
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return(0);
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					model->horizontalAngle -= 0.1f;
					break;
				case SDLK_DOWN:
					model->horizontalAngle += 0.1f;
					break;
				case SDLK_RIGHT:
					model->verticalAngle += 0.1f;
					break;
				case SDLK_LEFT:
					model->verticalAngle -= 0.1f;
					break;
				case SDLK_ESCAPE:
					return (0);
					break;
				case SDLK_s:
					camera->position = vec3_sub(camera->position, vec3_mult_value(camera->dir, deltaTime * SPEED));
					break;
				case SDLK_w:
					camera->position = vec3_add(camera->position, vec3_mult_value(camera->dir, deltaTime * SPEED));
					break;
				case SDLK_a:
					camera->position = vec3_sub(camera->position, vec3_mult_value(camera->right, deltaTime * SPEED));
					break;
				case SDLK_d:
					camera->position = vec3_add(camera->position, vec3_mult_value(camera->right, deltaTime * SPEED));
					break;
				// case SDLK_KP_TAB:

				// 	break;

			}
		}
	}
	// printf("%f, %f, %f\n", right.x, right.y, right.z);
	// printf("camera = x : %f, y : %f, z : %f\n\n",camera->position.x,camera->position.y,camera->position.z);

	return (1);
}