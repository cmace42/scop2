#include "scop.h"

t_mat4 mat4_mult(t_mat4 m1, t_mat4 m2)
{
	t_mat4 res;
	size_t i;
	size_t j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
			j++;
		}
		i++;
	}
	return (res);
}