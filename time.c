#include "scop.h"

t_time getDataTime(t_time last)
{
	t_time new;

	new.currentTime = SDL_GetTicks();
	new.deltaTime = (float)(new.currentTime - last.lastTime);
	new.lastTime = new.currentTime;
	return (new);
}