#ifndef _MATHS_H_
#define _MATHS_H_

/* "maths" is used instead of "math" to avoid possible include conflicts */

#include "platform.h"

struct vector_t {
    /* angle is in degrees for greater precision than radians */
    fixed_t angle, mag;

    /* these are used to increase performance */
    fixed_t xcomp, ycomp;
};

void vect_resolve(struct vector_t*);

#endif
