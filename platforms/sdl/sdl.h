/* here's what a platform header needs to have #defined: */
/* FRACBITS - number of fractional bits to be used */
/* LCD_WIDTH - screen width */
/* LCD_HEIGHT - screen height */
/* LCD_RGBPACK(r,g,b) - packs RGB value into an integer */
/* FP_MUL(x,y) - fixed-point multiply with FRACBITS fractional bits */
/* FP_DIV(x,y) - fixed-point divide */

#include <SDL/SDL.h>

#include "platform.h"

#define FRACBITS 16
#define LCD_WIDTH 1280
#define LCD_HEIGHT 800
unsigned sdlplat_rgbpack(uint8_t, uint8_t, uint8_t);
#define LCD_RGBPACK(r,g,b) sdlplat_rgbpack(r,g,b)

#define FP_MUL(x,y) (long)((((long long)(x)) * ((long long)(y))) >> FRACBITS)
#define FP_DIV(x,y) (long)((((long long)(x)) << FRACBITS) / ((long long)(y)))
