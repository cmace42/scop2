#include "scop.h"

void reader_commentary(t_obj_reader *self)
{
	int16_t c;
	obj_reader_next(self);
	while((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		obj_reader_next(self);
	}
}

void reader_skip_wt(t_obj_reader *self)
{
	int16_t c;
	obj_reader_next(self);
	while((c = obj_reader_peek(self)) == ' ' && c != '\n' && c > 0)
	{
		obj_reader_next(self);
	}
}

int reader_numberInt(t_obj_reader *self)
{
	int16_t c;
	int result;

	result = 0;
	while ((c = obj_reader_peek(self)) != ' ' && c != '\n' && c > 0)
	{
		if (ft_isdigit(c))
		{
			result = result * 10 + (c - 48);
		}
		else if (c == '.')
		{
			break;
		}
		else if (c == ' ')
		{
			break;
		}
		else
		{
			printf("erreur l%ld,c%ld\n", self->line,self->column);
			break;
		}
		obj_reader_next(self);
	}
	return (result);
}

double render_numberDouble(t_obj_reader *self)
{
	int16_t c;
	double result;
	int i;

	i = 0;
	result = 0;
	while ((c = obj_reader_peek(self)) != ' ' && c != '\n' && c > 0)
	{
		if (ft_isdigit(c))
		{
			result = result * 10 + (c - 48);
			i++;
		}
		else
		{
			printf("erreur l%ld,c%ld\n", self->line,self->column);
			break;
		}
		obj_reader_next(self);
	}
	while (i--)
		result *= 0.1;
	return (result);
}

GLfloat *reader_number(t_obj_reader *self, GLfloat *result)
{
	int16_t c;
	double num1;
	double num2;
	int sign = 1;
	int i = 0;

	while((c = obj_reader_peek(self))!= '\n' && c > 0)
	{
		reader_skip_wt(self);
		if ((c = obj_reader_peek(self)) == '-')
		{
			sign = -1;
			obj_reader_next(self);
		}
		num1 = reader_numberInt(self);
		c = obj_reader_peek(self);
		if (obj_reader_peek(self) == '.')
		{
			obj_reader_next(self);
			num2 = render_numberDouble(self);
		}
		result[i] = (GLfloat)((num1 + num2) * (double)sign);
		sign = 1;
		i++;
	}
	return (result);
}

t_vec3 reader_uv(t_obj_reader *self)
{
	int16_t c;
	t_vec3 vertices;

	while((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		obj_reader_next(self);
	}
}

t_vec3 reader_normal(t_obj_reader *self)
{
	int16_t c;
	t_vec3 vertices;

	while((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		obj_reader_next(self);
	}
}

GLfloat *getVertices(GLfloat *v, GLfloat *newVertices, int size)
{
	size_t i;
	GLfloat *vertices;

	vertices = (GLfloat*)malloc(sizeof(GLfloat) * (size + 3));
	i = 0;
	while (i < 3)
	{
		vertices[size + i] = newVertices[i];
		i++;
	}
	if (size != 0)
	{
		i = 0;
		while(i < size)
		{
			vertices[i] = v[i];
			i++;
		}
		free(v);
	}
	return (vertices);
}

bool loadObj(t_model *obj, char *filepath)
{
	char	*line;
	int fd = open(filepath, O_RDONLY);
	char buffer[4096];
	GLfloat *vertices;
	int16_t c;
	t_obj_reader r;
	r = obj_create_reader(fd, buffer, 4096);
	c = 'a';
	int size = 0;

	while((c = obj_reader_peek(&r))> 0)
	{
		if (c == '#')
		{
			reader_commentary(&r);
		}
		else if (c == 'v')
		{
			obj_reader_next(&r);
			if (c == 't')
			{
				printf("uv\n");
				reader_uv(&r);
			}
			else if (c == 'n')
			{
				printf("normal\n");
				reader_normal(&r);
			}
			else
			{
				// printf("vertices\n");
				GLfloat result[3];
				reader_number(&r, &result[0]);
				vertices = getVertices(vertices, &result[0], size);
				size += 3;
			}
		}
		// if (c == 'f')
			// printf("face\n");
		obj_reader_next(&r);
	}
	free(vertices);

	return (true);
}