#include "scop.h"

int event()
{
	SDL_Event event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	{
		return(0);
	}
	return (1);
}