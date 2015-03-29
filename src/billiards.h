#ifndef _BILLIARDS_H_
#define _BILLIARDS_H_

#include "ball.h"

int billiards_main(void);

#define BALL_RADIUS 20

struct billiards_ctx_t {
    struct ball_t balls[10];
};

#endif
