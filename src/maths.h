#include "platform.h"

struct vector_t {
    /* angle is in degrees for simplicity's sake */
    fixed_t angle, mag;

    /* these are used to increase performance */
    fixed_t dx, dy;
};
