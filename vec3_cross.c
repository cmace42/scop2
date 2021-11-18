#include "scop.h"

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    return ((t_vec3){
        a.y * b.z - b.y * a.z,
        a.z * b.x - b.z * a.x,
        a.x * b.y - b.x * a.y});
}