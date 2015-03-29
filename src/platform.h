#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/* provides a basic abstraction layer and some useful macros */

#include "../platforms/rockbox/rockbox.h"

/* some convenience macros */
#undef ARRAYLEN
#define ARRAYLEN(x) (sizeof(x)/sizeof(x[0]))

#define FIXED(x) ((x)<<FRACBITS)

#define RANDRANGE(a, b) (plat_rand()%(b-a)+a)

/* rounds x to nearest integer */
#define FP_ROUND(x) (((x)+(1<<(FRACBITS-1)))>>FRACBITS)

#define FLOAT_TO_FIXED(x) (FP_ROUND((x)*(1<<FRACBITS)))

/* fixed_t is a fixed-point type with FRACBITS fractional bits */
/* FRACBITS is platform-dependent */
typedef long fixed_t;

void plat_init(void);

void plat_set_background(unsigned);
void plat_set_foreground(unsigned);
void plat_hline(int x1, int x2, int y);
void plat_vline(int y1, int y2, int x);
void plat_drawpixel(int x, int y);
void plat_drawrect(int x, int y, int w, int h);
void plat_fillrect(int x, int y, int w, int h);
void plat_filltri(int x1, int y1, int x2, int y2, int x3, int y3);
void plat_fillcircle(int cx, int cy, int r);
void plat_log(const char *str);
void plat_logf(const char *fmt, ...);

void plat_lcd_update(void);

/* these take and return fixed-point values */
/* NOTE: rockbox version converts to integer degree value */
fixed_t plat_sin(fixed_t);
fixed_t plat_cos(fixed_t);

unsigned int plat_rand(void);

/* seeds the RNG with a platform-specific value such as the time */
void plat_srand(void);

#endif
