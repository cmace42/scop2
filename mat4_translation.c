#include "scop.h"

t_mat4 mat4_translation(t_vec3 offset)
{
	return ((t_mat4)
	{
		.m =
		{
			{1.0, 0.0, 0.0, offset.x},
			{0.0, 1.0, 0.0, offset.y},
			{0.0, 0.0, 1.0, offset.z},
			{0.0, 0.0, 0.0, 1.0}
		}
	});
}
