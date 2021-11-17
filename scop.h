#ifndef SCOP_H
# define SCOP_H

# define GL_GLEXT_PROTOTYPES

# include <stddef.h>
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include <SDL2/SDL_opengl_glext.h>
# include <assert.h>
# include <stdbool.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600


typedef struct	s_vec2
{
	float x;
	float y;
}				t_vec2;

typedef struct	s_vec3
{
	float x;
	float y;
	float z;
}				t_vec3;

typedef struct	s_vec4
{
	float x;
	float y;
	float z;
	float w;
}				t_vec4;

typedef struct s_info
{
	SDL_Window		*window;
	SDL_GLContext	context;
}				t_info;

SDL_Window*		initWindow();
void			loop(GLuint vertexBuffer);
int				event();

GLuint			initOpenGL();
GLuint			loadShaders(const char *vertexSource, int vertexLen, 
							const char *fragmentSource, int fragmentLen);


#endif