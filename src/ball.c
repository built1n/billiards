#include "ball.h"
#include "maths.h"

void ball_step(struct ball_t *ball)
{
    /* move the specified ball */
    ball->x += ball->motion.xcomp;
    ball->y += ball->motion.ycomp;

    /* check if it collided with a wall */
    if(ball->x <= FIXED(ball->radius) || ball->x >= FIXED(LCD_WIDTH - ball->radius))
    {
        ball->motion.angle = (FIXED(180) - ball->motion.angle) % FIXED(360);
        //ball->motion.mag = FP_MUL(ball->motion.mag, BALL_ELASTICITY);
        vect_resolve(&ball->motion);
        ball->x += FP_MUL(2, ball->motion.xcomp);
        ball->y += FP_MUL(2, ball->motion.ycomp);
    }
    if(ball->y <= FIXED(ball->radius) || ball->y >= FIXED(LCD_HEIGHT - ball->radius))
    {
        ball->motion.angle = (FIXED(360) - ball->motion.angle) % FIXED(360);
        //ball->motion.mag = FP_MUL(ball->motion.mag, BALL_ELASTICITY);
        vect_resolve(&ball->motion);
        ball->x += FP_MUL(2, ball->motion.xcomp);
        ball->y += FP_MUL(2, ball->motion.ycomp);
    }

    /* apply friction, currently very primitive */
    //ball->motion.mag = FP_MUL(ball->motion.mag, FP_DIV(FIXED(999), FIXED(1000)));
    //vect_resolve(&ball->motion);
}

static inline void docollide(struct ball_t *b1, struct ball_t *b2)
{
    fixed_t x1 = b1->x, y1 = b1->y;
    fixed_t x2 = b2->x, y2 = b2->y;
    fixed_t dist_sqr = FP_MUL(x1-x2, x1-x2) + FP_MUL(y1-y2, y1-y2);
    if(dist_sqr < FIXED((2 * b1->radius) * (2 * b1->radius)))
    {
        b1->color = LCD_RGBPACK(RANDRANGE(0,255),
                                RANDRANGE(0,255),
                                RANDRANGE(0,255));
        fixed_t dist = plat_sqrt(dist_sqr);
        //plat_logf("collide distance: %f", (double) dist / (1<<FRACBITS));
        b1->motion.angle += FIXED(180);
        vect_resolve(&b1->motion);
        b2->motion.angle += FIXED(180);
        vect_resolve(&b2->motion);

    }
}

void ball_check_collisions(struct ball_t *balls, int len)
{
    for(unsigned int i = 0; i < len; ++i)
    {
        for(unsigned int j = i + 1; j < len; ++j)
        {
            docollide(balls+i, balls+j);
        }
    }
}
