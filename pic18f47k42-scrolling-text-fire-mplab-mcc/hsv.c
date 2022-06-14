#include "hsv.h"


void fast_hsv2rgb_8bit(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b)
{
	HSV_MONOCHROMATIC_TEST(s, v, r, g, b);	// Exit with grayscale if s == 0

	uint8_t sextant = h >> 8;

	HSV_SEXTANT_TEST(sextant);		// Optional: Limit hue sextants to defined space

	HSV_POINTER_SWAP(sextant, r, g, b);	// Swap pointers depending which sextant we are in

	*g = v;		// Top level

	// Perform actual calculations
	uint8_t bb;
	uint16_t ww;

	/*
	 * Bottom level: v * (1.0 - s)
	 * --> (v * (255 - s) + error_corr) / 256
	 */
	bb = ~s;
	ww = v * bb;
	ww += 1;		// Error correction
	ww += ww >> 8;		// Error correction
	*b = ww >> 8;

	uint8_t h_fraction = h & 0xff;	// 0...255

	if(!(sextant & 1)) {
		// *r = ...slope_up...;
		/*
		 * Slope up: v * (1.0 - s * (1.0 - h))
		 * --> (v * (255 - (s * (256 - h) + error_corr1) / 256) + error_corr2) / 256
		 */
		ww = !h_fraction ? ((uint16_t)s << 8) : (s * (uint8_t)(-h_fraction));
		ww += ww >> 8;		// Error correction 1
		bb = ww >> 8;
		bb = ~bb;
		ww = v * bb;
		ww += v >> 1;		// Error correction 2
		*r = ww >> 8;
	} else {
		// *r = ...slope_down...;
		/*
		 * Slope down: v * (1.0 - s * h)
		 * --> (v * (255 - (s * h + error_corr1) / 256) + error_corr2) / 256
		 */
		ww = s * h_fraction;
		ww += ww >> 8;		// Error correction 1
		bb = ww >> 8;
		bb = ~bb;
		ww = v * bb;
		ww += v >> 1;		// Error correction 2
		*r = ww >> 8;

		/*
		 * A perfect match for h_fraction == 0 implies:
		 *	*r = (ww >> 8) + (h_fraction ? 0 : 1)
		 * However, this is an extra calculation that may not be required.
		 */
	}
}


struct color ColorHSV(uint8_t h, uint8_t s, uint8_t v)
{
    struct color rgb;
    fast_hsv2rgb_8bit(h,s,v,&rgb.red,&rgb.blue,&rgb.green);
    return rgb;
}

struct color ColorRGB(uint8_t r,uint8_t g,uint8_t b)
{
    struct color ret;
    ret.red = r;
    ret.green = g;
    ret.blue = b;
    return ret;
}

uint8_t scale(uint8_t c, uint8_t b)
{
    uint16_t t;
    t = c * b;
    t /= 256;
    return t;
}

void pixel_set_color(int x, int y, struct color c, uint8_t brightness)
{
    uint16_t t;
    int address = x*8;
    if(x&1)
        address += y;
    else
        address += 7-y;
    
    c.red = scale(c.red,brightness);
    c.green = scale(c.green,brightness);
    c.blue = scale(c.blue,brightness);

    if(address < 256)
        frameBuffer[address] = c;
}


void scroller(void)
{
    static int x = 33;
    
    x --;
    if(x == -(strlen(string)*8))
    {
        x = 32;
    }

    if(x == 32)
        fb_clear();
    else
    {
        fb_moveto(x,0);
        fb_drawString(string);
    }
}
void wopr(void)
{
    fb_moveto(rand()&31,rand()&7);
    if(rand() & 1) fb_setPixel();
    else fb_clrPixel();
}

void spinner(void)
{
    static uint8_t x0=0,x1=31,y0=0,y1=7;
    static uint8_t stage = 0;

    fb_clear();
    fb_moveto(x0,y0);
    fb_lineto(x1,y1);

    switch(stage)
    {
        case 0:
            x0 ++;
            x1 --;
            if(x1 == 0) stage = 1;
            break;
        case 1:
            y0 ++;
            y1 --;
            if(y1 == 0 ) stage = 2;
            break;
        case 2:
            x0 --;
            x1 ++;
            if(x0 == 0) stage = 3;
            break;
        case 3:
            y0 --;
            y1 ++;
            if(y0 == 0 ) stage = 0;
            break;
    }
}

void showPlasma(void)
{
    for(int y=0;y<8;y++)
        for(int x=0;x<32;x++)
        {
            fb_moveto(x,y);
            fb_setPixel();
        }
}


uint8_t buttonPress(void)
{
    static uint8_t debouncer = 3;
    uint8_t ret = 0;
    
    if(s1_GetValue() == 0)
    {
        led2_SetHigh();
        debouncer = 3;
    }
    else
    {
        led2_SetLow();
        if(debouncer)
        {
            debouncer --;
        }
        else
        {
            ret = 1;
        }
    }
    return ret;
}

uint8_t colorMode()
{
    static uint8_t button_pv=0;
    static uint8_t mode;
    uint8_t button;
    
    button = buttonPress();
    if(button && (button != button_pv))
    {
        mode ++;
        if(mode > 2) mode = 0;
    }
    button_pv = button;
    
    return mode;
}

struct color plasma(int x, int y, int phase)
{
    int value = 0;
    int phase1,phase2;
    int phase3;
    long t1,t2,t3;
    uint8_t color;

    phase1 = sin8(phase);
    phase2 = cos8(phase);
    phase1 *= 2;
    phase2 *= 3;
    phase3 = sin8u(phase);
    value  = sin8u((phase3 * x)/16 + phase1);
    value += cos8u((phase3 * y)/16 + phase2);
    
    t1 = x * sin8(phase/2);
    t2 = y * cos8(phase/3);
    t3 = (10 * (t1 + t2));
    t3 += phase;
    t3 %= 256;
    // value += sin8u(t3);
    //value += sin8u( ( 10 * (x * sin8(phase/4) + (y * cos8(phase/6))) ) + phase);
    
    return ColorRGB(sin8u(value),sin8u(value+85),sin8u(value+171));
}

uint8_t sin8u(int theta)
{
    return sin8(theta) + 128;
}

uint8_t cos8u(int theta)
{
    return cos8(theta) + 128;
}

// integer sine for ± Pi radians
// this is the SAME as 
int8_t sin8(int theta)
{
    theta %= 256;
    theta += 128;
    return sinc[theta%256];
}

int8_t cos8(int theta)
{
    return sinc[(theta-64)%256];
}

// dumb algorithm.. will get faster later
uint8_t sqrti(int n)
{
    int x = n;
    int y = 1;
    int x_pv = -1;
    int y_pv = -1;
    while(x > y)
    {
        x = (x + y) / 2;
        y = n / x;
        if(x == x_pv && y == y_pv) break;
        x_pv = x;
        y_pv = y;
    }
    return x;
}


struct color fire(int x, int y)
{
    // average adjacent pixels together upwards... ignore the pixel below the current pixel
    if(x==0)
        p1[y+1][x] = (p1[y][x] + p1[y+1][BUF_WIDTH-1]+p1[y][x+1]+p1[y-1][x]) / 4;
    else if(x==BUF_WIDTH-1)
        p1[y+1][x] = (p1[y][x]+p1[y][x-1]+p1[y-1][0]+p1[y-1][x]) / 4;
    else
        p1[y+1][x] = (p1[y][x]+p1[y][x-1]+p1[y][x+1]+p1[y-1][x]) / 4;

    // decay the color (cool the fire)
    if(p1[y][x] > 30)
        p1[y][x] -= 30;
    else if(p1[y][x] > 11)
        p1[y][x] -= 12;
    else if(p1[y][x] > 3)
        p1[y][x] -= 4;
    else
    {
        if(p1[y][x] > 0) p1[y][x]--;
        if(p1[y][x] > 0) p1[y][x]--;
        if(p1[y][x] > 0) p1[y][x]--;
    }
        
    return pal[p1[y][x]];
}


void randomizeFire(void)
{
    static int rate = RATE_LIMIT;
    int delta = 0;
    
    if(rate)
    {
        rate --;
    }
    else
    {
        rate = RATE_LIMIT;
        for(int x=0;x<BUF_WIDTH;x++)
        {
            if((rand()&0x0F) < 8)
            {
                delta=(rand()&1)*255;
            }
            p1[0][x] = delta;
        }
    }
}
