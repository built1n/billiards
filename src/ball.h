#include "platform.h"

struct ball_t {
    fixed_t x, y;
    fixed_t radius;

    struct vector_t motion;
};
