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

typedef struct	s_mat4
{
	float m[4][4];
}				t_mat4;

typedef struct s_info
{
	SDL_Window		*window;
	SDL_GLContext	context;
}				t_info;

/* Init */
SDL_Window*		initWindow();
GLuint			initOpenGL();

/* main prog */

void			loop(GLuint vertexBuffer, SDL_Window *window);
int				event(t_vec2 *angleModel);
void			applyPerspective(GLuint programId, float xAngModel, float yAngModel);

/* Tools */
GLuint			loadShaders(const char *vertexSource, int vertexLen, 
					const char *fragmentSource, int fragmentLen);
t_mat4			initPerspective (float fov, float zNear, float zFar);
t_mat4			lookAt(t_vec3 cameraPosition, t_vec3 cameraTarget, t_vec3 upVector);
t_mat4			initModelMatrice(float xAngle, float yAngle);

/* Math */

t_mat4		mat4_identity(void);
t_mat4		mat4_mult(t_mat4 m1, t_mat4 m2);
t_mat4		mat4_rotation_x(float angle);
t_mat4		mat4_rotation_y(float angle);
t_mat4		mat4_rotationz(float angle);
t_mat4		mat4_scaling(t_vec3 scale);
t_mat4		mat4_translation(t_vec3 offset);
t_vec3		vec3_new(float x, float y, float z);
t_vec3		vec3_normalisation(t_vec3 vec);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_div(t_vec3 a, t_vec3 b);
t_vec3		vec3_div_value(t_vec3 a, float value);
t_vec3		vec3_mult(t_vec3 a, t_vec3 b);
t_vec3		vec3_mult_value(t_vec3 a, float value);
t_vec3		vec3_normalisation(t_vec3 vec);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);

void		printMat4(t_mat4 mat);

float		ToRadian(float angle);

float		vec3_length(t_vec3 v);


#endif