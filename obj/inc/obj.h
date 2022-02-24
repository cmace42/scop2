#ifndef OBJ_H
# define OBJ_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "../../libft/libft.h"

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

typedef struct s_facesPerLine
{
	size_t len;
	size_t size;
	size_t *this;
}				t_facesPerLine;

typedef struct s_faces_array
{
	size_t len;
	size_t size;
	t_triangle *triangle;
	t_facesPerLine fpl;
}				t_faces_array;

typedef struct s_groupe
{
	char *name;
	t_faces_array faces;
}				t_groupe;

typedef enum	e_face_type
{
	Obj_No_Type,
	Obj_Vertex_Type,
	Obj_Normal_Type,
	Obj_Texture_Type,
	Obj_Vertex_Texture_Normal_Type,
}				t_face_type;

typedef struct s_obj
{
	size_t size;
	size_t len;
	t_vertex_array vertex;
	t_vertex_array vn;
	t_uv_array vt;
	t_groupe	*groupe;
	t_face_type	type;
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
	WRONG_TYPE = -11,
	WRONG_VERTEX_TYPE_IN_FACE = -12,
	WRONG_NORMAL_TYPE_IN_FACE = - 13,
	NO_VERTEX = -14,
	NO_FACES = -15,
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
/*
*	int obj_get_vertex(t_vertex_array *vertex_array, t_obj_reader *reader)
*	vertex_array : array de vertex (x y z)[]
*	t_obj_reader : pointe sur le reader
*	retourne un int contenant l'erreur
*/
int obj_get_vertex(t_vertex_array *vertex_array, t_obj_reader *reader);
/*
*	int obj_get_uv(t_uv_array *vertex_array, t_obj_reader *reader)
*	vertex_array : array de vertex (u v w)[]
*	t_obj_reader : pointe sur le reader
*	retourne un int contenant l'erreur
*/
int obj_get_uv(t_uv_array *uv_array, t_obj_reader *reader);

/*
*	int obj_append_vertex(t_vertex_array *vertex_array, t_vertex vertex)
*	vertex_array : array contenant tous les vertex
*	vertex : nouveau vertex a ajouter;
*	retourn un int en fonction de l'erreur
*/
int obj_append_vertex(t_vertex_array *vertex_array, t_vertex vertex);
/*
*	int obj_append_uv(t_uv_array *uv_array, t_uv uv)
*	uv_array : array contenant tous les uv
*	uv : nouveau vertex a ajouter;
*	retourn un int en fonction de l'erreur
*/
int obj_append_uv(t_uv_array *uv_array, t_uv uv);
/*
*	int obj_read(t_obj *obj, char *filepath)
*	*obj : pointe sur le nouvel obj
*	filepath : fichier a parser
*	retourne un entier erreur;
*/
int obj_read(t_obj *obj, char *filepath, t_obj_reader *reader);

int obj_skip_whitespace(t_obj_reader *self);

/*
* 	void printobj(t_obj obj);
*	obj : l'obj complet avec tous les datas
*	print les arrays
*/
void  printobj(t_obj obj);

/*
*	int obj_get_triangles_index(t_faces_array *faces, t_obj_reader *reader)
*	
*/
int obj_get_triangles_index(t_faces_array *faces, t_face_type *type, t_obj_reader *reader);


int obj_read_part_int(float *value, t_obj_reader *reader, int *sign);

int	obj_vertex_type(size_t *vertex, t_face_type *type, t_obj_reader *reader);
int	obj_uv_type(size_t *uv, t_face_type *type, t_obj_reader *reader, bool *haveNormal);
int obj_normal_type(size_t *normal, t_face_type *type, t_obj_reader *reader, bool *haveNormal);
int obj_append_triangle(t_faces_array *face, t_triangle triangle);
t_facesPerLine create_fpl_array(size_t size);
t_faces_array create_triangle_array(size_t size);
t_obj create_groupe(size_t size, t_face_type type);
t_groupe *obj_append_groupe(t_obj *obj, t_groupe groupe);
int obj_get_groupe(t_obj *obj, t_groupe **currentGroupe, t_obj_reader *reader);
int printError(t_obj_reader self, int error);
#endif