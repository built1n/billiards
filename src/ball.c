#include "ball.h"
#include "maths.h"

void ball_step(struct ball_t *balls, int idx)
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

    /* apply friction, currently very primitive */
    //balls[idx].motion.mag = FP_MUL(balls[idx].motion.mag, FP_DIV(FIXED(999), FIXED(1000)));
    //vect_resolve(&balls[idx].motion);

    /* now check if it collided with any balls */
    /* loop over every ball but the current one */
    /*
    for(int i = 0; i < idx; ++i)
    {
        fixed_t dx, dy;
        dx = balls[idx].x - old[i].x;
        dy = balls[idx].y - old[i].y;
        if(FP_MUL(dx, dx) + FP_MUL(dy, dy) < FIXED((2 * balls[idx].radius) * (2 * balls[idx].radius)))
        {
            plat_logf("ball-to-ball collide %d to %d", idx, i);
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
            /plat_logf("ball-to-ball collide %d to %d", idx, i);
            balls[idx].color = LCD_RGBPACK(RANDRANGE(0,255),
                                           RANDRANGE(0,255),
                                           RANDRANGE(0,255));
        }
    }
    */
}

static void docollide(struct ball_t *b1, struct ball_t *b2)
{
    fixed_t x1 = b1->x, y1 = b1->y;
    fixed_t x2 = b2->x, y2 = b2->y;
    fixed_t dist_sqr = FP_MUL(x1-x2, x1-x2) + FP_MUL(y1-y2, y1-y2);
    if(dist_sqr < FIXED((2 * b1->radius) * (2 * b1->radius)))
    {
        b1->color = LCD_RGBPACK(RANDRANGE(0,255),
                                RANDRANGE(0,255),
                                RANDRANGE(0,255));
    }
}

void ball_check_collisions(struct ball_t *balls, int len)
{
    for(unsigned int i = 0; i < len; ++i)
    {
        for(unsigned int j = 0; j < i; ++j)
        {
            docollide(balls+i, balls+j);
        }
        for(unsigned int j = i + 1; j < len; ++j)
        {
            docollide(balls+i, balls+j);
        }
    }
}
