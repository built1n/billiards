#include "maths.h"
#include "platform.h"

void vect_resolve(struct vector_t* vect)
{
    vect->xcomp = FP_MUL(vect->mag, plat_cos(vect->angle));
    vect->ycomp = FP_MUL(vect->mag, plat_sin(vect->angle));
}
