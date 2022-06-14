#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fb_driver.h"

#define maxColumns 32
static uint8_t frame_buffer[maxColumns] = {0};
static int16_t x_pos = 0;
static int16_t y_pos = 0;
static const font_t *currentFont = NULL;
static bool invertColors = false;

static void setPixel(int16_t x, int16_t y, int8_t p)
{
    uint8_t mask = 0x80 >> y;
        
	if(y >= 0 && y < 8)
	{
		if(x >= 0 && x < maxColumns)
		{
            if(p)
    			frame_buffer[x] |= mask;
            else
                frame_buffer[x] &= ~mask;
		}
	}
}

static int8_t getPixel(int16_t x, int16_t y)
{
    uint8_t ret = 0;
    uint8_t mask = 0x80 >> y;
	if(y >= 0 && y < 8)
	{
		if(x >= 0 && x < maxColumns)
		{
            ret = frame_buffer[x] & mask;
		}
	}
    return ret;
}

uint8_t fb_getPixel(void)
{
    return getPixel(x_pos,y_pos);
}

void fb_setPixel(void)
{
    setPixel(x_pos,y_pos,1);
}

void fb_clrPixel(void)
{
    setPixel(x_pos,y_pos,0);
}

void fb_init(void)
{
	fb_clear();
}

void fb_clear(void )
{
	memset(frame_buffer,0,sizeof(frame_buffer));
}

void fb_moveto(int16_t x, int16_t y)
{
	x_pos = x;
	y_pos = y;
}

#define abs(a) (((a)<0)?-(a):(a))

void fb_lineto(int16_t x, int16_t y)
{
   int8_t dx =  abs(x-x_pos), sx = x_pos<x ? 1 : -1;
   int8_t dy = -abs(y-y_pos), sy = y_pos<y ? 1 : -1; 
   int8_t err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      setPixel(x_pos,y_pos,1);
      if (x_pos==x && y_pos==y) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x_pos += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y_pos += sy; } /* e_xy+e_y < 0 */
   }
}

void fb_setFont(const font_t *fontPtr)
{
	currentFont = fontPtr;
}

void fb_drawString(const char *string)
{
	// draw string starting at x_pos,y_pos
    while(*string)
    {
        const font_t *l = &currentFont[*string];
        for(uint8_t c = 0; c < 8; c ++)
        {
            char p = l->bytes[c];
            // printf("%c %d %x\n",*string,c,p);
            if(x_pos > maxColumns) break;
            setPixel(x_pos,7,p&0x01);
            setPixel(x_pos,6,p&0x02);
            setPixel(x_pos,5,p&0x04);
            setPixel(x_pos,4,p&0x08);
            setPixel(x_pos,3,p&0x10);
            setPixel(x_pos,2,p&0x20);
            setPixel(x_pos,1,p&0x40);
            setPixel(x_pos,0,p&0x80);
            x_pos ++;
        }
        string ++;
    }
}

void fb_shiftLeft(void)
{
	// shift the frame buffer left one pixel.  new pixels are off
}

void fb_shiftRight(void)
{
	// shift the frame buffer right one pixel. new pixels are off
}

void fb_shiftUp(void)
{
	// shift the frame buffer up one pixel. new pixels are off
}

void fb_shiftDown(void)
{
	// shift the frame buffer down one pixel. new pixels are off
}

void fb_colorInvert(void)
{
	invertColors = true;
}

void fb_colorNormal(void)
{
	invertColors = false;
}

void fb_drawPage(void)
{
	// ignore the invert colors for now
}
