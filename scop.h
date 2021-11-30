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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include "libft/libft.h"

# define WIDTH 800
# define HEIGHT 600
# define SPEED 0.0009f
# define MOUSESPEED 0.00005f
# define INITIALFOV 45.0f

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

typedef struct s_vao
{
	GLuint VertexArrayID;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint textureBuffer;
}				t_vao;

typedef struct s_camera
{
	t_vec3 position;
	t_vec3 target;
	t_vec3 up;
}				t_camera;

typedef struct	s_obj_reader
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	len;
	size_t	i;
	size_t	column;
	size_t	line;
}				t_obj_reader;

typedef struct s_model
{
	t_vec3 vertices;
	t_vec2 uvs;
	t_vec3 normals;
}				t_model;

// typedef struct	s_list
// {
// 	double			number;
// 	size_t			content_size;
// 	struct s_list	*next;
// }				t_list;

/* Init */
SDL_Window*		initWindow();
t_vao			initOpenGL();

/* main prog */

void			loop(t_vao vao, SDL_Window *window);
int event(t_vec2 *angleModel, t_camera *camera, t_vec3 right, float deltaTime, t_vec3 dir);
void			applyPerspective(GLuint programId, float xAngModel, float yAngModel, t_camera camera);

/* Tools */
bool			loadObj(t_model *obj, char *filepath);
GLuint			loadShaders(const char *vertexSource, int vertexLen, 
					const char *fragmentSource, int fragmentLen);
t_mat4			initPerspective (float fov, float zNear, float zFar);
t_mat4			lookAt(t_vec3 cameraPosition, t_vec3 cameraTarget, t_vec3 upVector);
t_mat4			initModelMatrice(float xAngle, float yAngle);
GLuint			loadBMP_custom(const char *imagepath);
int				get_next_line(const int fd, char **line);
t_obj_reader	obj_create_reader(int fd, char *buffer, size_t buffer_size);
int16_t			obj_reader_peek(t_obj_reader *self);
void			obj_reader_next(t_obj_reader *self);


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