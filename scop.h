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

# define WIDTH 1600
# define HEIGHT 1200
# define SPEED 0.009f
# define MOUSESPEED 0.00005f
# define INITIALFOV 70.0f

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

typedef struct	s_bufferData
{
	GLfloat *buffer_data;
	size_t size_data;
}				t_bufferData;

typedef struct s_model
{
	t_bufferData vertex;
	t_bufferData uv;
	t_bufferData normal;
	GLfloat *vertex_buffer_data;
	size_t vertex_size_data;
	GLfloat *uv_buffer_data;
	size_t uv_size_data;
	GLfloat *normal_buffer_data;
	size_t normal_size_data;
}				t_model;

typedef struct	s_listParsing
{
	GLfloat			number;
	struct s_listParsing	*next;
	struct s_listParsing	*prev;
}				t_listParsing;

/*vUv = Vertex Uv*/
typedef struct s_listData
{
	t_listParsing *vertices;
	t_listParsing *vUv;
	t_listParsing *vNormal;
	t_listParsing *facesV;
	t_listParsing *facesUv;
	t_listParsing *facesNormal;
	int nVertices;
	int nUv;
	int nNormal;
	int nFacesV;
	int nFacesUv;
	int nFacesNormal;
}				t_listData;

enum {
	DONE,
	WRONG_CHAR,
	NO_RESULT,
	GET_RESULT,
	GET_FLOAT,
	RIP_MALLOC,
	RIP_OPEN,
	RIP_READ,
	PREVIOUS_NODE_CANT_BE_NULL,
	FACE_ID_OVERFLOW,
	FACE_ID_CANT_BE_ZERO,
	NO_DATA,
	UV_NORMAL_NOT_EQUAL_TO_VERTEX,
};

/* Init */
SDL_Window*		initWindow();
t_vao initOpenGL(t_model obj);

/* main prog */

void			loop(t_vao vao, SDL_Window *window, t_model obj);
int event(t_vec2 *angleModel, t_camera *camera, t_vec3 right, float deltaTime, t_vec3 dir);
void			applyPerspective(GLuint programId, float xAngModel, float yAngModel, t_camera camera);

/* Tools */
int				loadObj(char *filepath, t_model *model);
GLuint			loadShaders(const char *vertexSource, int vertexLen, 
					const char *fragmentSource, int fragmentLen);
t_mat4			initPerspective (float fov, float zNear, float zFar);
t_mat4			lookAt(t_vec3 cameraPosition, t_vec3 cameraTarget, t_vec3 upVector);
t_mat4			initModelMatrice(float xAngle, float yAngle);
GLuint			loadBMP_custom(const char *imagepath);
t_obj_reader	obj_create_reader(int fd, char *buffer, size_t buffer_size);
int16_t			obj_reader_peek(t_obj_reader *self);
int				obj_reader_next(t_obj_reader *self);

/* Tools Parsing */
void printList(t_listParsing* node);
void printListR(t_listParsing* node);
int append(t_listParsing** head_ref, GLfloat new_data);
int insertAfter(t_listParsing *prev_node, GLfloat new_data);
int push(t_listParsing** head_ref, GLfloat new_data);
void freeList(t_listParsing **head_ref);

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