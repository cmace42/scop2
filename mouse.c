#include "scop.h"

void mouseCamera(t_objectInWorld *camera, int *xMouse, int *yMouse, float deltaTime)
{
	SDL_GetRelativeMouseState(xMouse, yMouse);
	camera->angle.x += MOUSESPEED * deltaTime * (float)(*xMouse);
	camera->angle.y += MOUSESPEED * deltaTime * (float)(*yMouse);
	camera->dir = vec3_new(cosf(camera->angle.y) * sinf(camera->angle.x),
			sinf(camera->angle.y),
			cosf(camera->angle.y) * cosf(camera->angle.x));
	camera->right = vec3_new(sinf(camera->angle.x - 3.14f/2.0f),
			0,
			cosf(camera->angle.x - 3.14f/2.0f));
	camera->up = vec3_cross(camera->right, camera->dir);
	camera->target = vec3_add(camera->position, camera->dir);
}