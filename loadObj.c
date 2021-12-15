#include "scop.h"

int reader_skip_nextline(t_obj_reader *self)
{
	int16_t c;

	obj_reader_next(self);
	while((c = obj_reader_peek(self)) > 0 && c != '\n')
	{
		if (obj_reader_next(self) == -1)
			return(RIP_READ);
	}
	if (c == -1)
		return (RIP_READ);
	return (DONE);
}

int reader_skip_wt(t_obj_reader *self)
{
	int16_t c;

	while((c = obj_reader_peek(self)) > 0 && (c == ' ' || c == '\t') && c != '\n')
	{
		// printf("'%d' ", c);
		if (obj_reader_next(self) == -1)
			return (RIP_READ);
		// printf("%d\n",obj_reader_peek(self));
	}
	if (c == -1)
		return (RIP_READ);
	return (DONE);
}

int reader_numberInt(t_obj_reader *self, int *result, bool forFace)
{
	int16_t c;
	int ret;

	ret = NO_RESULT;
	*result = 0;
	while ((c = obj_reader_peek(self)) > 0 && c != ' ' && c != '\n')
	{
		// printf("%c, ",c);
		if (ft_isdigit(c))
		{
			*result = *result * 10 + (c - 48);
			ret = GET_RESULT;
		}
		else if (c == '.')
		{
			return (GET_FLOAT);
		}
		else if (c == ' ' || c == '\t' || c == '\n' || (forFace && c == '/'))
			return(ret);
		else
		{
			// printf("erreur l%ld,c%ld : '%c'\n", self->line,self->column, c);
			return (WRONG_CHAR);
		}
		if (obj_reader_next(self) == -1)
			return (RIP_READ);
	}
	// printf("\n");
	if (c == -1)
		return (RIP_READ);
	return (ret);
}

int render_numberGLfloat(t_obj_reader *self, GLfloat *result, bool forFace)
{
	int16_t c;
	int i;

	i = 0;
	*result = 0;
	while ((c = obj_reader_peek(self)) > 0 && c != ' ' && c != '\n')
	{
		if (ft_isdigit(c))
		{
			*result = *result * 10 + (c - 48);
			i++;
		}
		else if (c == ' ' || c == '\t' || (forFace && c == '/'))
		{
			// printf("%f\n", *result);
			break;
		}
		else 
		{
			// printf("erreur l%ld,c%ld : '%c'\n", self->line,self->column, c);
			return (WRONG_CHAR);
		}
		if (obj_reader_next(self) == -1)
			return(RIP_READ);
	}
	if (c == -1)
		return (RIP_READ);
	while (i--)
		*result *= 0.1;
	return (GET_RESULT);
}

int printError(t_obj_reader *self, int error)
{
	int ret;
	if (error == WRONG_CHAR || error == NO_RESULT)
	{
		write(2, "Error line ", 11);
		ft_putnbr(self->line);
		write(2, ", col ", 6);
		ft_putnbr_fd(self->column, 2);
		write(2, " char : ", 8);
		if ((ret = obj_reader_peek(self)) == -1)
		{
			// printf("\n%d\n", ret);
			error = RIP_READ;
		}
		else if (ret == '\n' || ret == 0)
			write(2, "'\\n' OR 'EOF'. Need more data\n", 31);
		else if (ret >= 7 && ret <= 13)
		{
			write(2, "Non readable\n", 14);
		}
		else
		{
			write(2, "'", 1);
			write(2, &ret, 1);
			write(2, "'", 1);
			write(2, "\n", 1);
		}
	}
	else if (error == RIP_MALLOC)
		write(2, "Malloc error.\n", 15);
	else if (error == RIP_OPEN)
		write(2, "Scop can't open this.\n", 23);
	else if (error == RIP_READ)
		write(2, "Something wrong on read.\n", 26);
	else if (error == PREVIOUS_NODE_CANT_BE_NULL)
		write(2, "Previous node in chained list can't be null.\n", 46);
	else if (error == NO_DATA)
		write(2, "Need more data on file.\n", 25);
	else if (error == FACE_ID_OVERFLOW)
		write(2, "Face ID can't be highter than number of vertex.\n", 48);
	else if (error == FACE_ID_CANT_BE_ZERO)
		write(2, "Face ID can't be equals to zero or smaller.\n", 45);
	else if (error == UV_NORMAL_NOT_EQUAL_TO_VERTEX)
		write(2, "Uv or Normal need to be equal to vertex.\n", 42);
	return (error);
}

int reader_number(t_obj_reader *self, t_listParsing** vertices, bool uv)
{
	int16_t c;
	int num1;
	GLfloat num2;
	int sign = 1;
	int i;
	int ret;

	i = 0;
	num1 = 0;
	num2 = 0;
	int n;
	n = uv ? 2 : 3;
	while(i < n)
	{
		if (reader_skip_wt(self) == RIP_READ)
			return (RIP_READ);
		if ((c = obj_reader_peek(self)) == '-')
		{
			sign = -1;
			if (obj_reader_next(self) == -1)
				return (RIP_READ);
		}
		else if (c == -1)
			return (RIP_READ);
		if ((ret = reader_numberInt(self, &num1, false)) == WRONG_CHAR || ret == RIP_READ || ret == NO_RESULT)
		{
			// printf("erreur l%ld,c%ld : '%c'\n", self->line,self->column, obj_reader_peek(self));
			return (ret);
		}
		else if (ret == GET_FLOAT)
		{
			if (obj_reader_next(self) == -1)
				return (RIP_READ);
			if ((ret = render_numberGLfloat(self, &num2, false)) != GET_RESULT)
				return (ret);
		}
		if (append(vertices, (((GLfloat)num1 + num2) * (GLfloat)sign)) == RIP_MALLOC)
			return(RIP_MALLOC);
		if (reader_skip_wt(self) == RIP_READ)
			return (RIP_READ);
		sign = 1;
		i++;
	}
	if ((c = obj_reader_peek(self)) != '\n')
	{
		if (reader_skip_nextline(self) == RIP_READ)
			return(RIP_READ);
	}
	else if (c == -1)
		return (RIP_READ);
	return (ret);
}

int reader_faces(t_obj_reader *self, t_listData *data)
{
	int16_t c;	
	int i;
	int indV[3];
	int indUv[3];
	int indNormal[3];
	int firstIndV;
	int firstIndUv;
	int firstIndNormal;
	int num;
	int ret;
	bool haveUv;

	i = 0;
	haveUv = false;
	bool haveNormal;
	haveNormal = false;
	while(i < 3)
	{
		if (reader_skip_wt(self) == RIP_READ)
			return (RIP_READ);
		if ((ret = reader_numberInt(self, &num, true)) != GET_RESULT)
			return(ret);
		if (append(&data->facesV, num) == RIP_MALLOC)
			return(RIP_MALLOC);
		indV[i] = num;
		data->nFacesV++;
		if (reader_skip_wt(self) == RIP_READ)
			return (RIP_READ);
		if ((c = obj_reader_peek(self)) == '/')
		{
			if (obj_reader_next(self) == -1)
				return (RIP_READ);
			if ((c = obj_reader_peek(self)) != '/' && c > -1 && i == 0 || haveUv)
			{
				haveUv = true;
				if ((ret = reader_numberInt(self, &num, true)) != GET_RESULT)
					return(ret);
				if (append(&data->facesUv, num) == RIP_MALLOC)
					return(RIP_MALLOC);
				indUv[i] = num;
				data->nFacesUv++;
				if (i == 0)
					firstIndUv = data->facesUv->number;
			}
			else if (c == '/')
			{
				haveNormal = true;
			}
			else if (c == -1)
				return (RIP_READ);
			else
				return (WRONG_CHAR);
		}
		else if (c == -1)
			return (RIP_READ);
		if ((c = obj_reader_peek(self)) == '/' && (i == 0 || haveNormal))
		{
			haveNormal = true;
			if (obj_reader_next(self) == -1)
				return (RIP_READ);
			if ((ret = reader_numberInt(self, &num, true)) != GET_RESULT)
				return(ret);
			if (append(&data->facesNormal, num) == RIP_MALLOC)
				return(RIP_MALLOC);
			indNormal[i] = num;
			data->nFacesNormal++;
			if (i == 0)
				firstIndNormal = data->facesNormal->number;
		}
		else if (haveNormal)
			return (WRONG_CHAR);
		else if (c == -1)
			return (RIP_READ);
		i++;
	}
	while((c = obj_reader_peek(self)) > 0 && c != '\n')
	{
		if (reader_skip_wt(self) == RIP_READ)
			return (RIP_READ);
		if (obj_reader_peek(self) != '\n')
		{
			if (append(&data->facesV, indV[0]) == RIP_MALLOC)
				return(RIP_MALLOC);
			if (append(&data->facesV, indV[2]) == RIP_MALLOC)
				return(RIP_MALLOC);
			int prov = indV[2];
			if ((ret = reader_numberInt(self, &indV[2], true)) != GET_RESULT)
				return (ret);
			if (append(&data->facesV, indV[2]) == RIP_MALLOC)
				return(RIP_MALLOC);
			data->nFacesV += 3;
			if ((c = obj_reader_peek(self)) == '/')
			{
				if (obj_reader_next(self) == -1)
					return (RIP_READ);
				if ((c = obj_reader_peek(self)) != '/' && c > -1 && haveUv)
				{
					if (append(&data->facesUv, indUv[0]) == RIP_MALLOC)
						return(RIP_MALLOC);
					if (append(&data->facesUv, indUv[2]) == RIP_MALLOC)
						return(RIP_MALLOC);
					if ((ret = reader_numberInt(self, &indUv[2], true)) != GET_RESULT)
						return (ret);
					if (append(&data->facesUv, indUv[2]) == RIP_MALLOC)
						return(RIP_MALLOC);
					data->nFacesUv+= 3;
				}
				else if (c == '/' && haveUv)
				{
					return (WRONG_CHAR);
				}
				else if (c == -1)
					return (RIP_READ);
			}
			else if (c == -1)
				return (RIP_READ);
			if ((c = obj_reader_peek(self)) == '/' && (haveNormal))
			{
				if (obj_reader_next(self) == -1)
					return (RIP_READ);
				if (append(&data->facesNormal, indNormal[0]) == RIP_MALLOC)
					return(RIP_MALLOC);
				if (append(&data->facesNormal, indNormal[2]) == RIP_MALLOC)
					return(RIP_MALLOC);
				if ((ret = reader_numberInt(self, &indNormal[2], true)) != GET_RESULT)
					return (ret);
				if (append(&data->facesNormal, indNormal[2]) == RIP_MALLOC)
					return(RIP_MALLOC);
				data->nFacesNormal+= 3;
			}
			else if (haveNormal)
			{
				printf("Coucou\n");
				return (WRONG_CHAR);
			}
			else if (c == -1)
				return (RIP_READ);
		}
	}
	if (c == -1)
		return (RIP_READ);
	// printList(data->facesV);
	// printList(data->facesUv);
	// printList(data->facesNormal);
	return (GET_RESULT);
}


int getDataListOfFile(char *filepath, t_listData *data, t_obj_reader *r)
{
	int16_t c;
	int ret;

	data->nVertices = 0;
	data->nUv = 0;
	data->nNormal = 0;
	data->nFacesV = 0;
	data->nFacesUv = 0;
	data->nFacesNormal = 0;
	data->vertices = NULL;
	data->facesV = NULL;
	data->facesUv = NULL;
	data->facesNormal = NULL;
	data->vUv = NULL;
	data->vNormal = NULL;
	while((c = obj_reader_peek(r)) > 0)
	{
		if (c == 'v')
		{
			obj_reader_next(r);
			c = obj_reader_peek(r);
			if (c == 't')
			{
				obj_reader_next(r);
				if ((ret = reader_number(r, &data->vUv, true)) != GET_RESULT)
					return (ret);
				data->nUv += 3;
			}
			else if (c == 'n')
			{
				obj_reader_next(r);
				if ((ret = reader_number(r, &data->vNormal, false)) != GET_RESULT)
					return (ret);
				data->nNormal += 3;
			}
			else if (c == -1)
			{
				return (RIP_READ);
			}
			else
			{
				if ((ret = reader_number(r, &data->vertices, false)) != GET_RESULT)
					return (ret);
				data->nVertices += 3;
			}
		}
		else if (c == 'f')
		{
			if (obj_reader_next(r) == RIP_READ)
				return (RIP_READ);
			if ((ret = reader_faces(r, data)) != GET_RESULT)
				return (ret);
		}
		else if (c == -1)
		{
			return (RIP_READ);
		}
		else
		{
			if (c != '#')
				printf("Warning : l%ld,c%ld : '%c'\n", r->line,r->column, c);
			if (reader_skip_nextline(r) == -1)
				return (RIP_READ);
		}
		if(obj_reader_next(r) == RIP_READ)
			return(RIP_READ);
	}
	// printf("vertices : %d, uv : %d, normal : %d, facesV : %d, facesUv : %d, facesNormal : %d\n", data->nVertices, data->nUv, data->nNormal, data->nFacesV, data->nFacesUv, data->nFacesNormal);
	// printList(data->vertices);
	// printList(data->vUv);
	// printList(data->vNormal);
	// printList(data->facesV);
	// printList(data->facesUv);
	// printList(data->facesNormal);
	return (GET_RESULT);
}

GLfloat *getTempBufferData(t_listParsing *data, int dataSize)
{
	GLfloat *buffer;
	// printf("%d\n", dataSize);
	if ((buffer = (GLfloat*)malloc(sizeof(GLfloat) * dataSize)) == NULL)
		return (NULL);
	int i;
	i = 0;
	while (data != NULL)
	{
		buffer[i] = data->number;
		data = data->next;
		i++;
	}
	return (buffer);
}

int getBufferData(GLfloat *tempBuffer, int sizeTempBuffer,t_listParsing *dataFaces, int faceSize, GLfloat** buffer)
{
	int i;

	printf("%i\n", faceSize);

	if((*buffer = (GLfloat*)malloc(sizeof(GLfloat) * faceSize * 3)) == NULL)
	{
		return (RIP_MALLOC);
	}
	printf("Start getBufferData : %d\n",sizeTempBuffer);
	i = 0;
	while(dataFaces != NULL)
	{
		if (dataFaces->number <= 0)
			return (FACE_ID_CANT_BE_ZERO);
		else if (dataFaces->number * 3 <= sizeTempBuffer)
		{
			(*buffer)[i] = tempBuffer[(int)dataFaces->number  * 3 - 3];
			i++;
			(*buffer)[i] = tempBuffer[(int)dataFaces->number * 3 - 2];
			i++;
			(*buffer)[i] = tempBuffer[(int)dataFaces->number * 3 - 1];
			i++;
		}
		else
		{
			// printf("Wrong data id[%d] on face\n", (int)dataFaces->number);
			return (FACE_ID_OVERFLOW);
		}
		dataFaces = dataFaces->next;
	}
	return (GET_RESULT);
}

int getTempsBuffersData(t_model *temp, t_listData data)
{
	if ((temp->vertex_buffer_data = getTempBufferData(data.vertices, data.nVertices)) != NULL)
	{
		if (data.vUv != NULL)
			if ((temp->uv_buffer_data = getTempBufferData(data.vUv, data.nUv)) == NULL)
				return (RIP_MALLOC);
		if (data.vNormal != NULL)
			if ((temp->normal_buffer_data = getTempBufferData(data.vNormal, data.nNormal)) == NULL)
				return (RIP_MALLOC);
	}
	else 
		return (RIP_MALLOC);
	return (GET_RESULT);
}

int getStaticUv(GLfloat* vertex, int size, GLfloat **uv, size_t *uvSize)
{
	int i;
	// size_t y;
	GLfloat xmin;
	GLfloat xmax;
	GLfloat ymin;
	GLfloat ymax;

	xmin = vertex[0];
	xmax = vertex[0];
	ymin = vertex[0 + 3];
	ymax = vertex[0 + 3];
	i = 3;
	*uvSize = 0;
	while(i < size)
	{
		xmin = vertex[i] > xmin ? xmin : vertex[i];
		xmax = vertex[i] < xmax ? xmax : vertex[i];
		ymin = vertex[i + 3] > ymin ? ymin : vertex[i + 3];
		ymax = vertex[i + 3] < ymax ? ymax : vertex[i + 3];
		i += 3;
		*uvSize += 2;
	}
	if((*uv = (GLfloat*)malloc(sizeof(GLfloat) * (*uvSize))) == NULL)
	{
		return (RIP_MALLOC);
	}
	i = 0;
	while (i < *uvSize)
	{
		(*uv)[i] = (xmin - vertex[i]) / xmax;
		(*uv)[i + 1] = (ymin - vertex[i + 3]) / ymax;
		i+= 2;
	}
	printf("xmin = %f xmax = %f\nymin = %f ymax = %f\n", xmin, xmax, ymin, ymax);
	return (GET_RESULT);
}

int loadObj(char *filepath, t_model *model)
{
	t_obj_reader r;
	t_listData data;
	t_model temp;
	int ret;
	char buffer[4096];


	int fd = open(filepath, O_RDONLY);
	if (fd > 0)
	{
		r = obj_create_reader(fd, buffer, 4096);
		model->vertex_buffer_data = NULL;
		temp.vertex_buffer_data = NULL;
		temp.uv_buffer_data = NULL;
		temp.normal_buffer_data = NULL;
		if ((ret = getDataListOfFile(filepath, &data, &r)) == GET_RESULT)
		{
			if (data.nVertices == 0 || data.nFacesV == 0)
				ret = NO_DATA;
			else
			{
				if ((ret = getTempsBuffersData(&temp, data)) == GET_RESULT)
				{
					// printf("sf%d\n", data.nFacesNormal);
					ret = getBufferData(temp.vertex_buffer_data, data.nVertices, data.facesV, data.nFacesV, &model->vertex_buffer_data);
					model->vertex_size_data = data.nFacesV;
					printf("%d == %d || %d == %d\n", data.nFacesV, data.nFacesNormal, data.nFacesV, data.nFacesUv);
					if (data.nFacesUv > 0 || data.nFacesNormal > 0)
					{
						if (data.nFacesV == data.nFacesUv || data.nFacesV == data.nFacesNormal)
						{
							if(temp.uv_buffer_data && data.vUv)
							{
								ret = getBufferData(temp.uv_buffer_data, data.nUv, data.facesUv, data.nFacesUv, &model->uv_buffer_data);
								model->uv_size_data = data.nFacesUv;
							}
							if (temp.normal_buffer_data && data.vNormal)
							{
								ret = getBufferData(temp.normal_buffer_data, data.nNormal, data.facesNormal, data.nFacesNormal, &model->normal_buffer_data);
								model->normal_size_data = data.nFacesNormal;
							}
						}
						else if (data.nFacesNormal != 0 || data.nFacesUv != 0)
							ret = UV_NORMAL_NOT_EQUAL_TO_VERTEX;
					}
					getStaticUv(model->vertex_buffer_data, model->vertex_size_data, &model->uv_static_buffer_data, &model->uv_static_size_data);
				}
			}
		}
		if (temp.vertex_buffer_data)
			free(temp.vertex_buffer_data);
		if (temp.uv_buffer_data)
			free(temp.uv_buffer_data);
		if (temp.normal_buffer_data)
			free(temp.normal_buffer_data);
		freeList(&data.vertices);
		freeList(&data.vUv);
		freeList(&data.vNormal);
		freeList(&data.facesV);
		freeList(&data.facesUv);
		freeList(&data.facesNormal);
	}
	else
		ret = RIP_OPEN;
	printError(&r, ret);
	return (ret);
}