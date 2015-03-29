/* here's what a platform header needs to have #defined: */
/* FRACBITS - number of fractional bits to be used */
/* LCD_WIDTH - screen width */
/* LCD_HEIGHT - screen height */
/* LCD_RGBPACK(r,g,b) - packs RGB value into an integer */
/* FP_MUL(x,y) - fixed-point multiply with FRACBITS fractional bits */
/* FP_DIV(x,y) */

#include "plugin.h"
#include "fixedpoint.h"

#define FRACBITS 14
#define FP_MUL(x,y) (fp_mul(x,y,FRACBITS))
#define FP_DIV(x,y) (fp_div(x,y,FRACBITS))
