/* provides a basic abstraction layer */

#include "../platforms/rockbox/rockbox.h"

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
void plat_log(const char *str);
void plat_logf(const char *fmt, ...);

void plat_lcd_update(void);
