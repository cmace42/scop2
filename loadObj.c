#include "scop.h"

void reader_skip_wt(t_obj_reader *self)
{
	int16_t c;

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
		else if (c == '.' || c == ' ' || c == '/')
		{
			break;
		}
		else
		{
			printf("erreur l%ld,c%ld : %c\n", self->line,self->column, c);
			break;
		}
		obj_reader_next(self);
	}
	return (result);
}

GLfloat render_numberGLfloat(t_obj_reader *self)
{
	int16_t c;
	GLfloat result;
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
		else if (c == ' ' || c == '/')
		{
			break;
		}
		else 
		{
			printf("erreur l%ld,c%ld : %c\n", self->line,self->column, c);
			break;
		}
		obj_reader_next(self);
	}
	while (i--)
		result *= 0.1;
	return (result);
}

void reader_number(t_obj_reader *self, t_listParsing** vertices)
{
	int16_t c;
	GLfloat num1;
	GLfloat num2;
	int sign = 1;

	while((c = obj_reader_peek(self))!= '\n' && c > 0)
	{
		reader_skip_wt(self);
		if (obj_reader_peek(self) == '-')
		{
			sign = -1;
			obj_reader_next(self);
		}
		num1 = reader_numberInt(self);
		if (obj_reader_peek(self) == '.')
		{
			obj_reader_next(self);
			num2 = render_numberGLfloat(self);
		}
		append(vertices, (GLfloat)((num1 + num2) * (GLfloat)sign));
		reader_skip_wt(self);
		sign = 1;
		if (obj_reader_peek(self) != '\n')
		{
			printf("Erreur l%ld:c%ld : '%c'\n",self->line,self->column, c);
		}
	}
	// printList(*vertices);
	printf("finish reader_number\n");
}

void reader_faces(t_obj_reader *self, t_listData *data)
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
	// firstIndV = getFirstIndexOfFace(self);
	i = 0;
	printf("start reader_faces\n");
	while(i < 3)
	{
		reader_skip_wt(self);
		num = reader_numberInt(self);
		append(&data->facesV, num);
		indV[i] = num;
		data->nFacesV++;
		reader_skip_wt(self);
		if ((c = obj_reader_peek(self)) == '/')
		{
			obj_reader_next(self);
			num = reader_numberInt(self);
			append(&data->facesUv, num);
			indUv[i] = num;
			data->nFacesUv++;
			if (i == 0)
				firstIndUv = data->facesUv->number;
		}
		if ((c = obj_reader_peek(self)) == '/')
		{
			obj_reader_next(self);
			num = reader_numberInt(self);
			append(&data->facesNormal, num);
			indNormal[i] = num;
			data->nFacesNormal++;
			if (i == 0)
				firstIndNormal = data->facesNormal->number;
		}
		i++;
	}
	while((c = obj_reader_peek(self))!= '\n' && c > 0)
	{
		reader_skip_wt(self);
		if (obj_reader_peek(self) != '\n')
		{
			append(&data->facesV, indV[0]);
			append(&data->facesV, indV[2]);
			int prov = indV[2];
			indV[2] =  reader_numberInt(self);
			append(&data->facesV, indV[2]);
			data->nFacesV += 3;
			if ((c = obj_reader_peek(self)) == '/')
			{
				obj_reader_next(self);
				append(&data->facesUv, indUv[0]);
				append(&data->facesUv, indUv[2]);
				indUv[2] =  reader_numberInt(self);
				append(&data->facesUv, indUv[2]);
				data->nFacesUv+= 3;
			}
			if ((c = obj_reader_peek(self)) == '/')
			{
				obj_reader_next(self);
				append(&data->facesNormal, indNormal[0]);
				append(&data->facesNormal, indNormal[2]);
				indNormal[2] =  reader_numberInt(self);
				append(&data->facesNormal, indNormal[2]);
				data->nFacesNormal+= 3;
			}
		}
	}
	printf("end reader_faces\n");
	// printListR(data->facesV);
	// printListR(data->facesV);
	// printListR(data->facesV);
	// printList(data->facesV);
	// printList(data->facesUv);
	// // printListR(data->facesNormal);
	// printList(data->facesNormal);
}

void reader_skip_nextline(t_obj_reader *self)
{
	int16_t c;

	obj_reader_next(self);
	while((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		obj_reader_next(self);
	}
}

t_listData getDataListOfFile(char *filepath)
{
	t_listData data;
	t_obj_reader r;
	int16_t c;
	char buffer[4096];

	data.nVertices = 0;
	data.nUv = 0;
	data.nNormal = 0;
	data.nFacesV = 0;
	data.nFacesUv = 0;
	data.nFacesNormal = 0;
	data.vertices = NULL;
	data.facesV = NULL;
	data.facesUv = NULL;
	data.facesNormal = NULL;
	data.vUv = NULL;
	data.vNormal = NULL;
	int fd = open(filepath, O_RDONLY);
	r = obj_create_reader(fd, buffer, 4096);
	while((c = obj_reader_peek(&r))> 0)
	{
		if (c == 'v')
		{
			obj_reader_next(&r);
			c = obj_reader_peek(&r);
			if (c == 't')
			{
				reader_number(&r, &data.vUv);
				data.nUv += 3;
			}
			else if (c == 'n')
			{
				reader_number(&r, &data.vNormal);
				data.nNormal += 3;
			}
			else
			{
				reader_number(&r, &data.vertices);
				data.nVertices += 3;
			}
		}
		else if (c == 'f')
		{
			obj_reader_next(&r);
			reader_faces(&r, &data);
		}
		else
		{
			reader_skip_nextline(&r);
		}
		obj_reader_next(&r);
	}
	// append(&data.vertices, -42);
	printf("vertices : %d, uv : %d, normal : %d, facesV : %d, facesUv : %d, facesNormal : %d\n", data.nVertices, data.nUv, data.nNormal, data.nFacesV, data.nFacesUv, data.nFacesNormal);
	// printList(data.vertices);
	// printList(data.vUv);
	// printList(data.vNormal);
	// printList(data.facesV);
	// printList(data.facesUv);
	// printList(data.facesNormal);
	return (data);
}

GLfloat *getTempBufferData(t_listParsing *data, int dataSize)
{
	GLfloat *buffer;
	buffer = (GLfloat*)malloc(sizeof(GLfloat) * dataSize);
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

GLfloat *getBufferData(GLfloat *tempBuffer, int sizeTempBuffer,t_listParsing *dataFaces, int faceSize)
{
	GLfloat *buffer;
	buffer = (GLfloat*)malloc(sizeof(GLfloat) * faceSize * 3);
	int i;
	int mul;
	int y;
	printf("Start getBufferData : %d\n",faceSize);
	i = 0;
	printList(dataFaces);
	while(dataFaces != NULL)
	{
		if (dataFaces->number < sizeTempBuffer * 3)
		{
			buffer[i] = tempBuffer[(int)dataFaces->number  * 3 - 3];
			// printf("%f ", buffer[i]);
			i++;
			buffer[i] = tempBuffer[(int)dataFaces->number *3 - 2];
			// printf("%f ", buffer[i]);
			i++;
			buffer[i] = tempBuffer[(int)dataFaces->number *3 -1];
			// printf("%f\n", buffer[i]);
			i++;
		}
		else
		{
			printf("Wrong data id[%d] on face\n", (int)dataFaces->number);
		}
		// printf("%d\n", (int)dataFaces->number);
		dataFaces = dataFaces->next;
	}
	printf("%d == %d\n", i, faceSize * 3);
	printf("end getBufferData\n");
	return (buffer);
}

t_model loadObj(char *filepath)
{
	t_listData data;
	t_model model;
	GLfloat *tempVertices;
	GLfloat *tempUv;
	GLfloat *tempNormal;

	tempVertices = NULL;
	tempUv = NULL;
	tempNormal = NULL;
	data = getDataListOfFile(filepath);
	tempVertices = getTempBufferData(data.vertices, data.nVertices);
	if (data.vUv != NULL)
		tempUv = getTempBufferData(data.vUv, data.nUv);
	if (data.vNormal != NULL)
		tempNormal = getTempBufferData(data.vNormal, data.nNormal);
	model.vertex_buffer_data = getBufferData(tempVertices, data.nVertices, data.facesV, data.nFacesV);
	model.vertex_size_data = data.nFacesV;
	if (tempVertices)
		free(tempVertices);
	if (tempUv)
		free(tempUv);
	if (tempNormal)
		free(tempNormal);
	freeList(&data.vertices);
	freeList(&data.vUv);
	freeList(&data.vNormal);
	freeList(&data.facesV);
	freeList(&data.facesUv);
	freeList(&data.facesNormal);
	return (model);
}