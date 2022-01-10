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

typedef struct s_vao
{
	GLuint VertexArrayID;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint textureBuffer;
}				t_vao;

typedef struct s_objectInWorld
{
	t_mat4 mod;
	t_vec3 position;
	t_vec3 target;
	t_vec3 up;
	t_vec3 dir;
	t_vec3 right;
	t_vec3 angle;
	t_vec3 whl;
	float width;
	float height;
	float lenght;
}				t_objectInWorld;

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
	GLfloat *uv_static_buffer_data;
	size_t uv_static_size_data;
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

typedef struct s_time
{
	float currentTime;
	float deltaTime;
	float lastTime;
}				t_time;

typedef struct s_okokok
{
	bool showTexture;
	GLuint	ShowTextureLoc;
	float transition;
	GLuint transitionLoc;
	bool test;
	GLuint	testLoc;
	int colorTest;
	GLuint colorTestLoc;
	t_vec3 bidouilleTest;
	GLuint bidouilleTestLoc;
}				t_okokok;

typedef struct s_env
{
	SDL_Window		*window;
	t_time			time;
	t_objectInWorld	camera;
	t_objectInWorld	model;
	t_model			modelData;
	t_vao			vao;
	GLuint			texture;
	GLuint			programId;
	// t_data			data;
	t_okokok ok;
	SDL_GLContext	context;
 }				t_env;

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
t_objectInWorld initCamera();
t_objectInWorld initModel(t_vec3 whl);


/* main prog */

void loop(t_env data);
int event(t_env *data, float deltaTime);	
void applyPerspective(GLuint programId, t_objectInWorld *model, t_objectInWorld *camera);
void render(t_env data);

/* Tools */
int				loadObj(char *filepath, t_model *model, t_vec3 *whl);
GLuint			loadShaders(const char *vertexSource, int vertexLen, 
					const char *fragmentSource, int fragmentLen);
t_mat4			initPerspective (float fov, float zNear, float zFar);
t_mat4			lookAt(t_vec3 cameraPosition, t_vec3 cameraTarget, t_vec3 upVector);
t_mat4			initModelMatrice(t_vec3 angle, t_vec3 whl, t_mat4 mat);
GLuint			loadBMP_custom(const char *imagepath);
t_obj_reader	obj_create_reader(int fd, char *buffer, size_t buffer_size);
int16_t			obj_reader_peek(t_obj_reader *self);
int				obj_reader_next(t_obj_reader *self);
t_time			getDataTime(t_time last);

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
t_mat4		mat4_rotation_z(float angle);
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