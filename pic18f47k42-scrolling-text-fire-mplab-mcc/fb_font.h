/* 
 * File:   fb_font.h
 * Author: c10948
 *
 * Created on June 16, 2016, 5:26 AM
 */

#ifndef FB_FONT_H
#define	FB_FONT_H

typedef struct 
{
    char bytes[8];
} font_t;

extern const font_t MAX7219_Dot_Matrix_font [256];

#endif	/* FB_FONT_H */

