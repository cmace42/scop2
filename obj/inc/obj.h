#ifndef OBJ_H
# define OBJ_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

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
	
	size_t size_data;
}				t_bufferData;

typedef struct	s_vertex
{
	float x;
	float y;
	float z;
}				t_vertex;

typedef struct	s_uv
{
	float u;
	float v;
	float w;
}				t_uv;

typedef struct s_vertex_array
{
	size_t size;
	size_t len;
	t_vertex *this;
}				t_vertex_array;

typedef struct s_uv_array
{
	size_t len;
	size_t size;
	t_uv *this;
}				t_uv_array;

typedef struct s_triangle_point
{
	size_t indexVertex;
	size_t indexUv;
	size_t indexNormal;
}				t_triangle_point;

typedef struct s_triangle
{
	t_triangle_point a;
	t_triangle_point b;
	t_triangle_point c;
}				t_triangle;

typedef struct s_faces_array
{
	size_t len;
	size_t size;
	t_triangle *triangle;
}				t_faces_array;

typedef struct s_groupe
{
	char *name;
	t_faces_array faces;
}				t_groupe;

typedef struct s_obj
{
	size_t size;
	t_vertex_array vertex;
	t_vertex_array vn;
	t_uv_array vt;
	t_groupe	*groupe;
}				t_obj;

enum {
	DONE,
	GET_RESULT,
	GET_FLOAT,
	RIP_READ = -1,
	NO_RESULT = -2,
	RIP_MALLOC = -3,
	RIP_OPEN = -4,
	WRONG_CHAR = -5,
	PREVIOUS_NODE_CANT_BE_NULL = -6,
	FACE_ID_OVERFLOW = -7,
	FACE_ID_CANT_BE_ZERO = -8,
	NO_DATA = -9,
	UV_NORMAL_NOT_EQUAL_TO_VERTEX = -10,
};

/*
*	t_obj_reader obj_create_reader(int fd, char *buffer, size_t buffer size)
*	fd : file descriptor
*	*buffer : chaine de charactere contenant le resultat lu par read
*	buffer_szie : taille du buffer
*	Cree un obj_reader
*/
t_obj_reader	obj_create_reader(int fd, char *buffer, size_t buffer_size);
/*
*	int16_t obj_reader_peek(t_obj_reader *self)
*	*self : pointeur sur self
*	récupère le char en cours
*/
int16_t			obj_reader_peek(t_obj_reader *self);
/*
*	int obj_reader_next(t_obj_reader *self)
*	*self : pointeur sur self
*	update le char en cours ainsi que les characteres qui seront lu, augmente
*	le nombre de colonne et ligne
*	retourne -1 en cas d'erreur
*/
int				obj_reader_next(t_obj_reader *self);

/*
*	t_vertex_array	create_vertex_array(size_t size)
*	size : taille du tableau a malloc
**	retourn la structure vertex_array
*/
t_vertex_array	create_vertex_array(size_t size);
/*
*	t_uv_array	create_vertex_array(size_t size)
*	size : taille du tableau a malloc
**	retourn la structure uv_array
*/
t_uv_array		create_uv_array(size_t size);

/*
*	int obj_skip_nl(t_obj_reader *self)
*	*self : pointe sur le reader
*	avance le reader jusqu'a la prochaine ligne
*	retourne RIP_READ (-1) ou GET_RESULT (2)
*/
int obj_skip_nl(t_obj_reader *self);

#endif