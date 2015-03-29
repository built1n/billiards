#include "ball.h"
#include "billiards.h"
#include "platform.h"

static void do_demo(void)
{
    struct ball_t balls[10];
    for(unsigned int i = 0; i < ARRAYLEN(balls); ++i)
    {
        balls[i].x = FIXED(RANDRANGE(BALL_RADIUS, LCD_WIDTH-BALL_RADIUS));
        balls[i].y = FIXED(RANDRANGE(BALL_RADIUS, LCD_HEIGHT-BALL_RADIUS));
        balls[i].radius = BALL_RADIUS;

        balls[i].color = LCD_RGBPACK(RANDRANGE(0,255),
                                     RANDRANGE(0,255),
                                     RANDRANGE(0,255));

        memset(&balls[i].motion, 0, sizeof(struct vector_t));
        balls[i].motion.angle = FIXED(RANDRANGE(0, 360));
        balls[i].motion.mag = FP_DIV(FIXED(3), FIXED(3));

        vect_resolve(&balls[i].motion);
    }
    while(1)
    {
        struct ball_t old[ARRAYLEN(balls)];
        memcpy(old, balls, sizeof(balls));
        plat_lcd_clear();
        for(unsigned int i = 0; i < ARRAYLEN(balls); ++i)
        {
            ball_step(balls, i, old, ARRAYLEN(balls));
            plat_set_foreground(balls[i].color);
            plat_fillcircle(balls[i].x >> FRACBITS, balls[i].y >> FRACBITS, balls[i].radius);
        }
        plat_lcd_update();
#ifdef PLAT_WANTS_YIELD
        plat_yield();
#endif
    }
}

/* this is called by the platform's main() or equivalent */
int billiards_main(void)
{
    plat_init();
    plat_srand();
    do_demo();
    return 0;
}
