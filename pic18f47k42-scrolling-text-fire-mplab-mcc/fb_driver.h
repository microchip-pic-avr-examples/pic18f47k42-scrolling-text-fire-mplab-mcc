// fb_driver.h

#ifndef __FB_DRIVER_H
#define __FB_DRIVER_H

#include <stdint.h>
#include "fb_font.h"

void fb_init(void);
void fb_clear(void);
void fb_moveto(int16_t x, int16_t y);
void fb_lineto(int16_t x, int16_t y);
uint8_t fb_getPixel(void);
void fb_setPixel(void);
void fb_clrPixel(void);
void fb_setFont(const font_t *fontPtr);
void fb_drawString(const char *string);
void fb_shiftLeft(void);
void fb_shiftRight(void);
void fb_shiftUp(void);
void fb_shiftDown(void);
void fb_colorInvert(void);
void fb_colorNormal(void);
void fb_drawPage(void);

#endif // __FB_DRIVER_H
