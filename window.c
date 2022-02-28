#include "scop.h"

SDL_Window *initWindow()
{
	SDL_Window *window;
	printf("Initialisation SDL2...\n");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	window = SDL_CreateWindow("Scop", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	printf("SDL2 initialised\n");
	return (window);
}