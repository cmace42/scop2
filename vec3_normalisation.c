#include "scop.h"

t_vec3 vec3_normalisation(t_vec3 vec)
{
    return (vec3_div_value(vec, vec3_length(vec)));
}