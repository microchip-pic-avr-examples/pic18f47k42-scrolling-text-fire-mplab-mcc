/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef HSV_H
#define	HSV_H

#include <xc.h> 
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "fb_driver.h"

#define BUF_HEIGHT 8
#define BUF_WIDTH 32
#define PALETTE_SIZE 256

// edit this string for scrolling text
const char *string = "Welcome to Sensors Converge 2022 - Microchip Technology";

uint8_t p1[BUF_HEIGHT][BUF_WIDTH];

uint8_t sin8u(int theta);
uint8_t cos8u(int theta);
int8_t sin8(int theta);
int8_t cos8(int theta);
uint8_t sqrti(int a);

struct color
{
    uint8_t green;
    uint8_t red;
    uint8_t blue;
};

const struct color maskColor = {0,0,0};

struct color frameBuffer[256] = {{255,0,0},{0,255,0},{0,0,255},{128,128,128},{255,255,0},{0,255,0},{255,0,255}};

// table of sine values from 0 to 2Pi
const int8_t sinc[] = { 0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,
                        54,57,59,62,65,67,70,73,75,78,80,82,85,87,89,91,94,
                        96,98,100,102,103,105,107,108,110,112,113,114,116,
                        117,118,119,120,121,122,123,123,124,125,125,126,126,
                        126,126,126,127,126,126,126,126,126,125,125,124,123,
                        123,122,121,120,119,118,117,116,114,113,112,110,108,
                        107,105,103,102,100,98,96,94,91,89,87,85,82,80,78,75,
                        73,70,67,65,62,59,57,54,51,48,45,42,39,36,33,30,27,
                        24,21,18,15,12,9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-24,
                        -27,-30,-33,-36,-39,-42,-45,-48,-51,-54,-57,-59,-62,
                        -65,-67,-70,-73,-75,-78,-80,-82,-85,-87,-89,-91,-94,
                        -96,-98,-100,-102,-103,-105,-107,-108,-110,-112,-113,
                        -114,-116,-117,-118,-119,-120,-121,-122,-123,-123,
                        -124,-125,-125,-126,-126,-126,-126,-126,-127,-126,
                        -126,-126,-126,-126,-125,-125,-124,-123,-123,-122,
                        -121,-120,-119,-118,-117,-116,-114,-113,-112,-110,
                        -108,-107,-105,-103,-102,-100,-98,-96,-94,-91,-89,
                        -87,-85,-82,-80,-78,-75,-73,-70,-67,-65,-62,-59,-57,
                        -54,-51,-48,-45,-42,-39,-36,-33,-30,-27,-24,-21,-18,
                        -15,-12,-9,-6,-3 };

// hsv code taken from here : http://www.vagrearg.org/content/hsvrgb#hsv256_256_256
// MIT license.  We should move this into its own file sometime
#define HSV_MONOCHROMATIC_TEST(s,v,r,g,b) \
	do { \
		if(!(s)) { \
			 *(r) = *(g) = *(b) = (v); \
			return; \
		} \
	} while(0)

#ifdef HSV_USE_SEXTANT_TEST
#define HSV_SEXTANT_TEST(sextant) \
	do { \
		if((sextant) > 5) { \
			(sextant) = 5; \
		} \
	} while(0)
#else
#define HSV_SEXTANT_TEST(sextant) do { ; } while(0)
#endif

/*
 * Pointer swapping:
 * 	sext.	r g b	r<>b	g<>b	r <> g	result
 *	0 0 0	v u c			!u v c	u v c
 *	0 0 1	d v c				d v c
 *	0 1 0	c v u	u v c			u v c
 *	0 1 1	c d v	v d c		d v c	d v c
 *	1 0 0	u c v		u v c		u v c
 *	1 0 1	v c d		v d c	d v c	d v c
 *
 * if(sextant & 2)
 * 	r <-> b
 *
 * if(sextant & 4)
 * 	g <-> b
 *
 * if(!(sextant & 6) {
 * 	if(!(sextant & 1))
 * 		r <-> g
 * } else {
 * 	if(sextant & 1)
 * 		r <-> g
 * }
 */
#define HSV_SWAPPTR(a,b)	do { uint8_t *tmp = (a); (a) = (b); (b) = tmp; } while(0)
#define HSV_POINTER_SWAP(sextant,r,g,b) \
	do { \
		if((sextant) & 2) { \
			HSV_SWAPPTR((r), (b)); \
		} \
		if((sextant) & 4) { \
			HSV_SWAPPTR((g), (b)); \
		} \
		if(!((sextant) & 6)) { \
			if(!((sextant) & 1)) { \
				HSV_SWAPPTR((r), (g)); \
			} \
		} else { \
			if((sextant) & 1) { \
				HSV_SWAPPTR((r), (g)); \
			} \
		} \
	} while(0)

void fast_hsv2rgb_8bit(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b);

struct color ColorHSV(uint8_t h, uint8_t s, uint8_t v);

struct color ColorRGB(uint8_t r,uint8_t g,uint8_t b);

uint8_t scale(uint8_t c, uint8_t b);

void pixel_set_color(int x, int y, struct color c, uint8_t brightness);

struct color plasma(int x, int y, int phase);
struct color fire(int i, int j);
void randomizeFire(void);

void scroller(void);

void scroller(void);

void wopr(void);

void spinner(void);

void showPlasma(void);

typedef void(*display_ptr)(void);
display_ptr displayFunctions[] = {wopr, scroller, spinner, showPlasma};

uint8_t buttonPress(void);

uint8_t colorMode();

struct color plasma(int x, int y, int phase);

uint8_t sin8u(int theta);

uint8_t cos8u(int theta);

// integer sine for ± Pi radians
// this is the SAME as 
int8_t sin8(int theta);

int8_t cos8(int theta);

uint8_t sqrti(int n);


// VGA color palette for flames
// green, blue, red
struct color pal[PALETTE_SIZE]={  
				{   0,  0,   0},{   0,  0,  24},{   0,  0,  24},{   0,  0,  28},
				{   0,  0,  32},{   0,  0,  32},{   0,  0,  36},{   0,  0,  40},
				{   0,  8,  40},{   0, 16,  36},{   0, 24,  36},{   0, 32,  32},
				{   0, 40,  28},{   0, 48,  28},{   0, 56,  24},{   0, 64,  20},
				{   0, 72,  20},{   0, 80,  16},{   0, 88,  16},{   0, 96,  12},
				{   0,104,   8},{   0,112,   8},{   0,120,   4},{   0,128,   0},
				{   0,128,   0},{   0,132,   0},{   0,136,   0},{   0,140,   0},
				{   0,144,   0},{   0,144,   0},{   0,148,   0},{   0,152,   0},
				{   0,156,   0},{   0,160,   0},{   0,160,   0},{   0,164,   0},
				{   0,168,   0},{   0,172,   0},{   0,176,   0},{   0,180,   0},
				{   4,184,   0},{   4,188,   0},{   8,192,   0},{   8,196,   0},
				{  12,200,   0},{  12,204,   0},{  16,208,   0},{  16,212,   0},
				{  20,216,   0},{  20,220,   0},{  24,224,   0},{  24,228,   0},
				{  28,232,   0},{  28,236,   0},{  32,240,   0},{  32,244,   0},
				{  36,252,   0},{  36,252,   0},{  40,252,   0},{  40,252,   0},
				{  44,252,   0},{  44,252,   0},{  48,252,   0},{  48,252,   0},
				{  52,252,   0},{  52,252,   0},{  56,252,   0},{  56,252,   0},
				{  60,252,   0},{  60,252,   0},{  64,252,   0},{  64,252,   0},
				{  68,252,   0},{  68,252,   0},{  72,252,   0},{  72,252,   0},
				{  76,252,   0},{  76,252,   0},{  80,252,   0},{  80,252,   0},
				{  84,252,   0},{  84,252,   0},{  88,252,   0},{  88,252,   0},
				{  92,252,   0},{  96,252,   0},{  96,252,   0},{ 100,252,   0},
				{ 100,252,   0},{ 104,252,   0},{ 104,252,   0},{ 108,252,   0},
				{ 108,252,   0},{ 112,252,   0},{ 112,252,   0},{ 116,252,   0},
				{ 116,252,   0},{ 120,252,   0},{ 120,252,   0},{ 124,252,   0},
				{ 124,252,   0},{ 128,252,   0},{ 128,252,   0},{ 132,252,   0},
				{ 132,252,   0},{ 136,252,   0},{ 136,252,   0},{ 140,252,   0},
				{ 140,252,   0},{ 144,252,   0},{ 144,252,   0},{ 148,252,   0},
				{ 152,252,   0},{ 152,252,   0},{ 156,252,   0},{ 156,252,   0},
				{ 160,252,   0},{ 160,252,   0},{ 164,252,   0},{ 164,252,   0},
				{ 168,252,   0},{ 168,252,   0},{ 172,252,   0},{ 172,252,   0},
				{ 176,252,   0},{ 176,252,   0},{ 180,252,   0},{ 180,252,   0},
				{ 184,252,   0},{ 184,252,   0},{ 188,252,   0},{ 188,252,   0},
				{ 192,252,   0},{ 192,252,   0},{ 196,252,   0},{ 196,252,   0},
				{ 200,252,   0},{ 200,252,   0},{ 204,252,   0},{ 208,252,   0},
				{ 208,252,   0},{ 208,252,   0},{ 208,252,   0},{ 208,252,   0},
				{ 212,252,   0},{ 212,252,   0},{ 212,252,   0},{ 212,252,   0},
				{ 216,252,   0},{ 216,252,   0},{ 216,252,   0},{ 216,252,   0},
				{ 216,252,   0},{ 220,252,   0},{ 220,252,   0},{ 220,252,   0},
				{ 220,252,   0},{ 224,252,   0},{ 224,252,   0},{ 224,252,   0},
				{ 224,252,   0},{ 228,252,   0},{ 228,252,   0},{ 228,252,   0},
				{ 228,252,   0},{ 228,252,   0},{ 232,252,   0},{ 232,252,   0},
				{ 232,252,   0},{ 232,252,   0},{ 236,252,   0},{ 236,252,   0},
				{ 236,252,   0},{ 236,252,   0},{ 240,252,   0},{ 240,252,   0},
				{ 240,252,   0},{ 240,252,   0},{ 240,252,   0},{ 244,252,   0},
				{ 244,252,   0},{ 244,252,   0},{ 244,252,   0},{ 248,252,   0},
				{ 248,252,   0},{ 248,252,   0},{ 248,252,   0},{ 252,252,   0},
				{ 252,252,   4},{ 252,252,   8},{ 252,252,  12},{ 252,252,  16},
				{ 252,252,  20},{ 252,252,  24},{ 252,252,  28},{ 252,252,  32},
				{ 252,252,  36},{ 252,252,  40},{ 252,252,  40},{ 252,252,  44},
				{ 252,252,  48},{ 252,252,  52},{ 252,252,  56},{ 252,252,  60},
				{ 252,252,  64},{ 252,252,  68},{ 252,252,  72},{ 252,252,  76},
				{ 252,252,  80},{ 252,252,  84},{ 252,252,  84},{ 252,252,  88},
				{ 252,252,  92},{ 252,252,  96},{ 252,252, 100},{ 252,252, 104},
				{ 252,252, 108},{ 252,252, 112},{ 252,252, 116},{ 252,252, 120},
				{ 252,252, 124},{ 252,252, 124},{ 252,252, 128},{ 252,252, 132},
				{ 252,252, 136},{ 252,252, 140},{ 252,252, 144},{ 252,252, 148},
				{ 252,252, 152},{ 252,252, 156},{ 252,252, 160},{ 252,252, 164},
				{ 252,252, 168},{ 252,252, 168},{ 252,252, 172},{ 252,252, 176},
				{ 252,252, 180},{ 252,252, 184},{ 252,252, 188},{ 252,252, 192},
				{ 252,252, 196},{ 252,252, 200},{ 252,252, 204},{ 252,252, 208},
				{ 252,252, 208},{ 252,252, 212},{ 252,252, 216},{ 252,252, 220},
				{ 252,252, 224},{ 252,252, 228},{ 252,252, 232},{ 252,252, 236},
				{ 252,252, 240},{ 252,252, 244},{ 252,252, 248},{ 252,252, 252}};


struct color fire(int x, int y);

#define RATE_LIMIT 2
void randomizeFire(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* HSV_H */

