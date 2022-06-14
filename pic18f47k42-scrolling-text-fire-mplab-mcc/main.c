/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F46K42
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "fb_driver.h"
#include "hsv.h"



void main(void)
{
    int idx = 0;
    int counter = 1000;
    int phase = 0;
    struct color v;
    struct color hColor;
    uint8_t mask;
    uint8_t column=0;
    
    unsigned int brightness_value = 0;
    unsigned int hue_value = 0;
    
    // Initialize the device
    SYSTEM_Initialize();
    fb_init();
    fb_setFont(MAX7219_Dot_Matrix_font);
    
    while (1)
    {
        ADCC_SelectChannel(hue,0);
        ADCC_StartConversion();
        
        // get the time...
        while(!TMR1_HasOverflowOccured()); // wait for overflow...
        // GO!
        TMR1_ResetOverflow();
        TMR1_Reload();
        
        led1_SetHigh();
        
        displayFunctions[idx]();
        if(--counter == 0)
        {
            counter = 600;
            if(++idx > sizeof(displayFunctions)/(sizeof(*displayFunctions))) idx = 0;
        }
            
        hue_value = ADCC_GetConversionResult();
        hue_value >>= 8;

        ADCC_SelectChannel(brightness,0);
        ADCC_StartConversion();
    
        
        
        hColor = ColorHSV(hue_value,255,255);
        
        // compute the background
        for(int x=0;x<32;x++)
        {
            for(int y=0;y<8;y++)
            {
                
                // switch here based upon a toggle of a switch...
                switch(colorMode())
                {
                    case 0:
                        v = hColor;
                        break;
                    case 1:
                        v = plasma(x,y,phase);
                        break;
                    case 2:
                    default:
                        v = fire(x,y);
                        break;
                }
                
                fb_moveto(x,y);
                if(fb_getPixel())
                    pixel_set_color(x,y,v,brightness_value);
                else
                    pixel_set_color(x,y,maskColor,brightness_value);
            }
        }

        brightness_value = ADCC_GetConversionResult();
        brightness_value >>= 9;
        
        // update the timer
        phase ++;
        if(phase >= 4 * 256) phase = 1;
        randomizeFire();

        led1_SetLow();
        
        // render the screen
        SPI1_half_duplex_send(frameBuffer, sizeof(frameBuffer));        
    }
}

