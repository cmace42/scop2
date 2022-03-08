/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:08:49 by cmace             #+#    #+#             */
/*   Updated: 2022/03/08 14:05:48 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "obj.h"

# define WIDTH 1600
# define HEIGHT 1200
# define SPEED 0.009f
# define SPEEDBOOST 0.014f
# define MOUSESPEED 0.00005f
# define INITIALFOV 70.0f
# define MAXDIST 1000.0f

# define KEYMESSAGE "+---------------+-------------------------------------------------------------------+\n\
| Scop control  |                                                                   |\n\
+---------------+-------------------------------------------------------------------+\n\
| WASD          | Déplacement de la caméra                                          |\n\
| Numpad 824679 | fais tourner ou déplacer l'objet en fonction du mode              |\n\
| L             | Change le mode(Rotation/Translation) du model                     |\n\
| ZXC           | Change la couleur sur un R, G ou B                                |\n\
| O             | Change la couleur constamment                                     |\n\
| B             | Change la couleur du fond constamment                             |\n\
| U             | Active/Desactive le mode gris                                     |\n\
| P             | Transition entre mode texture/sans texture                        |\n\
| I             | Change le type d'affectation de couleur(Par face ou par triangle) |\n\
| K             | Active/Desactive le GL_CULL_FACE                                  |\n\
| + -           | Change la vitesse du changement de couleur du fond                |\n\
| pageUp        | Active/Desactive le GL_DEPTH_TEST                                 |\n\
| delete        | Affiche sommets/trait intersommet/faces                           |\n\
+---------------+-------------------------------------------------------------------+\n"

# define USAGE "Usage : ./scop [obj file]\n\
\t./scop [obj file] [bmp file]"
typedef struct s_vec2
{
	float	x;
	float	y;
}				t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4;

typedef struct s_mat4
{
	float	m[4][4];
}				t_mat4;

typedef struct s_vao
{
	GLuint	VertexArrayID;
	GLuint	vertexBuffer;
	GLuint	colorTrianglesBuffer;
	GLuint	colorFacesBuffer;
	GLuint	textureBuffer;
}				t_vao;

typedef struct s_objectInWorld
{
	t_mat4	this;
	t_vec3	position;
	t_vec3	target;
	t_vec3	up;
	t_vec3	dir;
	t_vec3	right;
	t_vec3	angle;
	t_vec3	whl;
	float	width;
	float	height;
	float	lenght;
}				t_objectInWorld;

typedef struct s_bufferData
{
	char	*name;
	GLfloat	*buffer_data;
	size_t	size_data;
}				t_bufferData;

typedef struct s_model
{
	size_t			size_groupe;
	t_bufferData	*vertex;
	t_bufferData	*uv;
	t_bufferData	*normal;
	t_bufferData	*colorFaces;
	t_bufferData	*colorTriangles;
}				t_model;

typedef struct s_time
{
	float	currentTime;
	float	deltaTime;
	float	lastTime;
}				t_time;

typedef struct s_action
{
	bool	showTexture;
	GLuint	ShowTextureLoc;
	float	transition;
	GLuint	transitionLoc;
	bool	autoColor;
	GLuint	autoColorLoc;
	t_vec3	color;
	GLuint	colorLoc;
	bool	rotate;
	bool	rotateKeyboardMode;
	bool	isBmp1;
	bool	haveSpeedBoost;
	int8_t	showFace;
	bool	showDept;
	bool	isFacesColor;
	bool	greymode;
	GLuint	greymodeLoc;
	bool	glcullface;
	GLuint	glcullfaceLoc;
	t_vec3	colorInc;
	bool	colorBackMode;
	t_vec3	colorBackground;
	float	speedColor;
}				t_action;

typedef struct s_bmp
{
	char			*data;
	unsigned int	width;
	unsigned int	height;
}				t_bmp;

typedef struct s_env
{
	SDL_Window		*window;
	t_time			time;
	t_objectInWorld	camera;
	t_objectInWorld	*model;
	t_model			modelData;
	t_vao			*vao;
	t_bmp			bmp[3];
	t_bmp			bmp1;
	t_bmp			bmp2;
	GLuint			texture;
	GLuint			programId;
	t_action		action;
	SDL_GLContext	context;
	float			speed;
}				t_env;

enum {
	MALLOCINITBUFFERFAILED = 100,
	READBUFFERFAILED,
	FAILEDTOINITMODEL,
	FAILEDTOINITWINDOW,
	FAILEDTOMALLOCMODEL,
	MDRCCASSER,
	FAILEDTOINITBMP,
	FAILEDTOINITVAO,
};

/* Init */
SDL_Window		*initWindow(void);
t_vao			*initOpenGL(t_model obj);
t_objectInWorld	initCamera(t_vec3 whl);
t_objectInWorld	*initModel(t_model modelData);
int				getModel(char *filename, t_model *model);
t_action		initAction(void);
int				init(t_env *env, char *filename, char *textureFilename);

/* main prog */

void			loop(t_env data);
int				eventTemp(void);
int				event(t_env *data, float deltaTime);	
void			applyPerspective(GLuint programId, t_objectInWorld *model, t_objectInWorld *camera);
void			render(t_env data);
t_action		interact(t_env data);

/* Tools */	
int				loadObj(char *filepath, t_model *model, t_vec3 *whl);
GLuint			loadShaders(const char *vertexSource, int vertexLen,
					const char *fragmentSource, int fragmentLen);
t_mat4			initPerspective(float fov, float zNear, float zFar);
t_mat4			lookAt(t_vec3 cameraPosition, t_vec3 cameraTarget, t_vec3 upVector);
t_mat4			initModelMatrice(t_vec3 angle, t_vec3 whl, t_vec3 pos);
int				loadBMP_custom(const char *imagepath, t_bmp *bmp);
t_time			getDataTime(t_time last);
GLuint			getTextureId(t_bmp bmp);
void			doRotate(t_objectInWorld **model, t_vec3 rotate, size_t size);
t_vec3			initAllWhl(t_objectInWorld *model, size_t size_groupe);
void			freeAll(t_env *env, int ret);
void			printModel(t_model model, t_face_type type);
void			mouseCamera(t_objectInWorld *camera, int *xMouse, int *yMouse, float deltaTime);

/* Math */

t_mat4			mat4_identity(void);
t_mat4			mat4_mult(t_mat4 m1, t_mat4 m2);
t_mat4			mat4_rotation_x(float angle);
t_mat4			mat4_rotation_y(float angle);
t_mat4			mat4_rotation_z(float angle);
t_mat4			mat4_scaling(t_vec3 scale);
t_mat4			mat4_translation(t_vec3 offset);
t_vec3			vec3_new(float x, float y, float z);
t_vec3			vec3_normalisation(t_vec3 vec);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_div(t_vec3 a, t_vec3 b);
t_vec3			vec3_div_value(t_vec3 a, float value);
t_vec3			vec3_mult(t_vec3 a, t_vec3 b);
t_vec3			vec3_mult_value(t_vec3 a, float value);
t_vec3			vec3_normalisation(t_vec3 vec);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
float			vec3_dot(t_vec3 a, t_vec3 b);
t_vec3			vec3_add_value(t_vec3 a, float value);
t_vec3			vec3_sub_value(t_vec3 a, float value);

void			printMat4(t_mat4 mat);

float			toRadian(float angle);

float			vec3_length(t_vec3 v);

#endif