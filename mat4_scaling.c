#include "scop.h"

t_mat4		mat4_scaling(t_vec3 scale)
{
      return ((t_mat4){
        .m = {
            {scale.x, 0.0, 0.0, 0.0},
            {0.0, scale.y, 0.0, 0.0},
            {0.0, 0.0, scale.z, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }
    });
}