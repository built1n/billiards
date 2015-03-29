#include "ball.h"
#include "maths.h"

void ball_step(struct ball_t *ball)
{
    ball->x += ball->motion.xcomp;
    ball->y += ball->motion.ycomp;
    if(ball->x < FIXED(ball->radius) || ball->x > FIXED(LCD_WIDTH - ball->radius))
    {
        ball->motion.angle = (FIXED(180) - ball->motion.angle) % FIXED(360);
        vect_resolve(&ball->motion);
        ball->x += ball->motion.xcomp;
        ball->y += ball->motion.ycomp;
    }
    if(ball->y < FIXED(ball->radius) || ball->y > FIXED(LCD_HEIGHT - ball->radius))
    {
        ball->motion.angle = (FIXED(360) - ball->motion.angle) % FIXED(360);
        vect_resolve(&ball->motion);
        ball->x += ball->motion.xcomp;
        ball->y += ball->motion.ycomp;
    }
}
