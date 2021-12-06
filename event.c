#include "scop.h"

int event(t_vec2 *angleModel, t_camera *camera, t_vec3 right, float deltaTime, t_vec3 dir)
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
					angleModel->y -= 0.1f;
					break;
				case SDLK_DOWN:
					angleModel->y += 0.1f;
					break;
				case SDLK_RIGHT:
					angleModel->x += 0.1f;
					break;
				case SDLK_LEFT:
					angleModel->x -= 0.1f;
					break;
				case SDLK_ESCAPE:
					return (0);
					break;
				case SDLK_s:
					camera->position = vec3_sub(camera->position, vec3_mult_value(dir, deltaTime * SPEED));
					break;
				case SDLK_w:
					camera->position = vec3_add(camera->position, vec3_mult_value(dir, deltaTime * SPEED));
					break;
				case SDLK_a:
					camera->position = vec3_sub(camera->position, vec3_mult_value(right, deltaTime * SPEED));
					break;
				case SDLK_d:
					camera->position = vec3_add(camera->position, vec3_mult_value(right, deltaTime * SPEED));
					break;
			}
		}
	}
	// printf("%f, %f, %f\n", right.x, right.y, right.z);
	// printf("camera = x : %f, y : %f, z : %f\n\n",camera->position.x,camera->position.y,camera->position.z);

	return (1);
}