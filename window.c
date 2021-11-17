#include "scop.h"

bool initWindow(SDL_Window *window)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (false);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	window = SDL_CreateWindow("Scop", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	assert(window);
	return (true);
}