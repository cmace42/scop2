#include "scop.h"

bool getBuffersModel(t_obj obj, t_model *model)
{
	if (initBuffer(t_model, ))
}

bool getModel(char *filename, t_model *model)
{
	t_obj_reader reader;
	t_obj obj;
	int ret;
	
	if ((ret = obj_read(&obj, filename, &reader)) != GET_RESULT)
	{
		printError(reader, ret);
		return (false);
	}
	printobj(obj);
	model = NULL;
	if (model)
		model = NULL;
	return (true);
}