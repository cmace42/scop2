#include "scop.h"

int event(t_vec2 *angleModel)
{
	SDL_Event event;



	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			printf("Really men ?\n");
			return(0);
		}
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
				}
		}
	}
	return (1);
}