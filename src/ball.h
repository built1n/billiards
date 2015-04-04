#ifndef _BALL_H_
#define _BALL_H_

#include "maths.h"
#include "platform.h"

/* balls have 90% elasticity */
#define BALL_ELASTICITY FP_DIV(FIXED(90),FIXED(100))

struct ball_t {
    /* all screenspace coordinates */
    fixed_t x, y;
    unsigned radius;
    unsigned color;

    struct vector_t motion;
};

/* updates the ball at balls[idx] while checking for collisions with balls in old[] */
void ball_step(struct ball_t *ball);

void ball_check_collisions(struct ball_t *balls, int len);

#endif
