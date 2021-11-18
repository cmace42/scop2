#include "scop.h"

t_mat4    mat4_identity(void)
{
    return ((t_mat4){
        .m = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }
    });
}