#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

#include <assert.h>
#include <math.h>
#include <time.h>

#include "sdl.h"

#include "../../src/billiards.h"
#include "../../src/platform.h"

static SDL_Surface *screen = NULL;
static uint32_t fgcol, bgcol;

void plat_init(void)
{
    plat_logf("SDL init");
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(LCD_WIDTH, LCD_HEIGHT, 32, SDL_HWSURFACE | SDL_HWACCEL);

    assert(screen != NULL);
    fgcol = LCD_RGBPACK(255,255,255);
    bgcol = LCD_RGBPACK(0,0,0);

    SDL_WM_SetCaption("Billiards", "Billiards");
    atexit(SDL_Quit);
}

void plat_lcd_clear(void)
{
    SDL_Rect fullrect = {0, 0, LCD_WIDTH, LCD_HEIGHT};
    SDL_FillRect(screen, &fullrect, bgcol);
}

void plat_set_background(unsigned col)
{
    bgcol = col;
}

void plat_set_foreground(unsigned col)
{
    fgcol = col;
}

/* hline is optimized and vline is not because hline is used for the drawing of circles */

void plat_hline(int x1, int x2, int y)
{
    if(y<0)
        return;
    uint8_t *left = screen->pixels + screen->pitch * y;
    uint8_t *right = left + x2 * 4;
    left += x1 * 4;
    while(left < right)
    {
        *(uint32_t*) left = fgcol;
        left += 4;
    }
}

void plat_vline(int y1, int y2, int x)
{
    SDL_Rect rect = {x, y1, 1, y2-y1};
    SDL_FillRect(screen, &rect, fgcol);
}

void plat_drawpixel(int x, int y)
{
    uint32_t *pix = screen->pixels;
    pix += screen->w * y;
    pix += x;
    *pix = fgcol;
}

void plat_drawrect(int x, int y, int w, int h)
{
    plat_hline(x, x+w, y);
    plat_hline(x, x+w, y+h);
    plat_vline(y, y+h, x);
    plat_vline(y, y+h, x+w);
}

void plat_fillrect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(screen, &rect, fgcol);
}

void plat_filltri(int x1, int y1, int x2, int y2, int x3, int y3)
{
    /* TODO */
}

void plat_log(const char *str)
{
    printf("%s\n", str);
}

void plat_logf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char buf[128];
    vsnprintf(buf, sizeof(buf), fmt, ap);
    printf("%s\n", buf);
    va_end(ap);
}

void plat_lcd_update(void)
{
    SDL_Flip(screen);
}

#define PI 3.141592653589793238462643383279502884197169399375105820974944592317816406286208998628

fixed_t plat_sin(fixed_t ang)
{
    double d = (double) ang / (1<<FRACBITS);
    d *= PI/180;
    return sin(d) * (1<<FRACBITS);
}

fixed_t plat_cos(fixed_t ang)
{
    double d = (double) ang / (1<<FRACBITS);
    d *= PI/180;
    return cos(d) * (1<<FRACBITS);
}

fixed_t plat_sqrt(fixed_t n)
{
    double d = (double) n / (1<<FRACBITS);
    return sqrt(d) * (1<<FRACBITS);
}

unsigned int plat_rand(void)
{
    return rand();
}

void plat_srand(void)
{
    srand(time(NULL));
}

void plat_fillcircle(int cx, int cy, int r)
{
    int d = 3 - (r * 2);
    int x = 0;
    int y = r;
    while(x <= y)
    {
        plat_hline(cx - x, cx + x, cy + y);
        plat_hline(cx - x, cx + x, cy - y);
        plat_hline(cx - y, cx + y, cy + x);
        plat_hline(cx - y, cx + y, cy - x);
        if(d < 0)
        {
            d += (x * 4) + 6;
        }
        else
        {
            d += ((x - y) * 4) + 10;
            --y;
        }
        ++x;
    }
}

unsigned int sdlplat_rgbpack(uint8_t r, uint8_t g, uint8_t b)
{
    return SDL_MapRGB(screen->format, r,g,b);
}

void plat_yield(void)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            exit(0);
        }
    }
}

int main(int argc, char* argv[])
{
    return billiards_main();
}
