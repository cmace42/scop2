#include "scop.h"

t_vec3		vec3_div(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.x / b.x,
		a.y / b.y,
		a.z / b.z
	});
}

t_vec3	vec3_div_value(t_vec3 a, float value)
{
	return ((t_vec3){
		a.x / value,
		a.y / value,
		a.z / value
	});
}