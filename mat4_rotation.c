#include "scop.h"

t_mat4  mat4_rotation_x(float angle)
{
    return ((t_mat4){
        .m = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, cos(angle), -sin(angle), 0.0},
            {0.0, sin(angle), cos(angle), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }
    });
}

t_mat4  mat4_rotation_y(float angle)
{
    return ((t_mat4){
        .m = {
            {cos(angle), 0.0, sin(angle), 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {-sin(angle), 0.0, cos(angle), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }
    });
}

t_mat4  mat4_rotationz(float angle)
{
    return ((t_mat4){
        .m = {
            {cos(angle), -sin(angle), 0.0, 0.0},
            {sin(angle), cos(angle), 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        }
    });
}