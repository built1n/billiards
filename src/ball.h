#ifndef _BALL_H_
#define _BALL_H_

#include "maths.h"
#include "platform.h"

struct ball_t {
    /* all screenspace coordinates */
    fixed_t x, y;
    unsigned radius;
    unsigned color;

    struct vector_t motion;
};

void ball_step(struct ball_t*);

#endif
