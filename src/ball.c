#include "ball.h"
#include "maths.h"

void ball_step(struct ball_t *balls, int idx, struct ball_t *old, int len)
{
    /* move the specified ball */
    balls[idx].x += balls[idx].motion.xcomp;
    balls[idx].y += balls[idx].motion.ycomp;

    /* check if it collided with a wall */
    if(balls[idx].x <= FIXED(balls[idx].radius) || balls[idx].x >= FIXED(LCD_WIDTH - balls[idx].radius))
    {
        balls[idx].motion.angle = (FIXED(180) - balls[idx].motion.angle) % FIXED(360);
        vect_resolve(&balls[idx].motion);
        balls[idx].x += 2*balls[idx].motion.xcomp;
        balls[idx].y += 2*balls[idx].motion.ycomp;
    }
    if(balls[idx].y <= FIXED(balls[idx].radius) || balls[idx].y >= FIXED(LCD_HEIGHT - balls[idx].radius))
    {
        balls[idx].motion.angle = (FIXED(360) - balls[idx].motion.angle) % FIXED(360);
        vect_resolve(&balls[idx].motion);
        balls[idx].x += 2*balls[idx].motion.xcomp;
        balls[idx].y += 2*balls[idx].motion.ycomp;
    }

    balls[idx].motion.mag = FP_MUL(balls[idx].motion.mag, FP_DIV(FIXED(999), FIXED(1000)));
    vect_resolve(&balls[idx].motion);

    /* now check if it collided with any balls */
    /* loop over every ball but the current one */
    for(int i = 0; i < idx; ++i)
    {
        fixed_t dx, dy;
        dx = balls[idx].x - old[i].x;
        dy = balls[idx].y - old[i].y;
        if(FP_MUL(dx, dx) + FP_MUL(dy, dy) < FIXED((2 * balls[idx].radius) * (2 * balls[idx].radius)))
        {
            //plat_logf("ball-to-ball collide %d to %d", idx, i);
            balls[idx].color = LCD_RGBPACK(RANDRANGE(0,255),
                                           RANDRANGE(0,255),
                                           RANDRANGE(0,255));

        }
    }
    for(int i = idx + 1; i < len; ++i)
    {
        fixed_t dx, dy;
        dx = balls[idx].x - old[i].x;
        dy = balls[idx].y - old[i].y;
        if(FP_MUL(dx, dx) + FP_MUL(dy, dy) < FIXED((2 * balls[idx].radius) * (2 * balls[idx].radius)))
        {
            //plat_logf("ball-to-ball collide %d to %d", idx, i);
            balls[idx].color = LCD_RGBPACK(RANDRANGE(0,255),
                                           RANDRANGE(0,255),
                                           RANDRANGE(0,255));

        }
    }
}
