#include "plugin.h"

#include "lib/xlcd.h"

#include "billiards.h"
#include "platform.h"

void plat_init(void)
{
}

void plat_set_background(unsigned col)
{
    rb->lcd_set_background(col);
}

void plat_set_foreground(unsigned col)
{
    rb->lcd_set_foreground(col);
}

void plat_hline(int x1, int x2, int y)
{
    rb->lcd_hline(x1, x2, y);
}

void plat_vline(int y1, int y2, int x)
{
    rb->lcd_vline(y1, y2, x);
}

void plat_drawpixel(int x, int y)
{
    rb->lcd_drawpixel(x, y);
}

void plat_drawrect(int x, int y, int w, int h)
{
    rb->lcd_drawrect(x, y, w, h);
}

void plat_fillrect(int x, int y, int w, int h)
{
    rb->lcd_fillrect(x, y, w, h);
}

void plat_filltri(int x1, int y1, int x2, int y2, int x3, int y3)
{
    xlcd_filltriangle(x1, y1,
                      x2, y2,
                      x3, y3);
}

void plat_log(const char *str)
{
    LOGF("%s", str);
}

void plat_logf(const char *fmt, ...)
{
#ifdef ROCKBOX_HAS_LOGF
    va_list ap;
    va_start(ap, fmt);
    char buf[128];
    rb->vsnprintf(buf, sizeof(buf), fmt, ap);
    LOGF("%s", buf);
    va_end(ap);
#endif
}

void plat_lcd_update(void)
{
    rb->lcd_update();
}

enum plugin_status plugin_start(const void *param)
{
    (void) param;
    int ret = billiards_main();
    if(ret == 0)
        return PLUGIN_OK;
    else
        return PLUGIN_ERROR;
}
