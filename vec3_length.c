#include "scop.h"

float vec3_length(t_vec3 vec)
{
    return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}