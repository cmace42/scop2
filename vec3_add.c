#include "scop.h"

t_vec3		vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	});
}