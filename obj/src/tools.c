#include "obj.h"

int obj_skip_nl(t_obj_reader *self)
{
	int16_t c;
	int ret;
	
	while((c = obj_reader_peek(self)) != '\n' && c > 0)
	{
		ret = obj_reader_next(self);
	}
	if (c == -1)
		return (RIP_READ);
	return (ret);
}

int obj_skip_whitespace(t_obj_reader *self)
{
	int16_t c;
	int ret;

	while((c = obj_reader_peek(self)) == ' ' || c == '\t' || c == '\r')
	{
		ret = obj_reader_next(self);
	}
	if (c == -1)
		return (RIP_READ);
	return (ret);
}