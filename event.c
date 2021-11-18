#include "scop.h"

int event(t_vec2 *angleModel)
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		{
			return(0);
		}
		if (SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
            	{
					 case SDLK_UP:
						angleModel->x += 0.1f;
						break;
					case SDLK_DOWN:
						angleModel->x -= 0.1f;
						break;
					case SDLK_RIGHT:
						angleModel->y += 0.1f;
						break;
					case SDLK_LEFT:
						angleModel->y -= 0.1f;
						break;
				}
		}
	}
	return (1);
}