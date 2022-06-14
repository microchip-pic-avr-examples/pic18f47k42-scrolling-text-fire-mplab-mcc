/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F47K42
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set brightness aliases
#define brightness_TRIS                 TRISAbits.TRISA0
#define brightness_LAT                  LATAbits.LATA0
#define brightness_PORT                 PORTAbits.RA0
#define brightness_WPU                  WPUAbits.WPUA0
#define brightness_OD                   ODCONAbits.ODCA0
#define brightness_ANS                  ANSELAbits.ANSELA0
#define brightness_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define brightness_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define brightness_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define brightness_GetValue()           PORTAbits.RA0
#define brightness_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define brightness_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define brightness_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define brightness_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define brightness_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define brightness_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define brightness_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define brightness_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set hue aliases
#define hue_TRIS                 TRISAbits.TRISA1
#define hue_LAT                  LATAbits.LATA1
#define hue_PORT                 PORTAbits.RA1
#define hue_WPU                  WPUAbits.WPUA1
#define hue_OD                   ODCONAbits.ODCA1
#define hue_ANS                  ANSELAbits.ANSELA1
#define hue_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define hue_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define hue_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define hue_GetValue()           PORTAbits.RA1
#define hue_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define hue_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define hue_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define hue_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define hue_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define hue_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define hue_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define hue_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set led1 aliases
#define led1_TRIS                 TRISAbits.TRISA4
#define led1_LAT                  LATAbits.LATA4
#define led1_PORT                 PORTAbits.RA4
#define led1_WPU                  WPUAbits.WPUA4
#define led1_OD                   ODCONAbits.ODCA4
#define led1_ANS                  ANSELAbits.ANSELA4
#define led1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define led1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define led1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define led1_GetValue()           PORTAbits.RA4
#define led1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define led1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define led1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define led1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define led1_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define led1_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define led1_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define led1_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set led2 aliases
#define led2_TRIS                 TRISAbits.TRISA5
#define led2_LAT                  LATAbits.LATA5
#define led2_PORT                 PORTAbits.RA5
#define led2_WPU                  WPUAbits.WPUA5
#define led2_OD                   ODCONAbits.ODCA5
#define led2_ANS                  ANSELAbits.ANSELA5
#define led2_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define led2_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define led2_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define led2_GetValue()           PORTAbits.RA5
#define led2_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define led2_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define led2_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define led2_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define led2_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define led2_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define led2_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define led2_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set led3 aliases
#define led3_TRIS                 TRISAbits.TRISA6
#define led3_LAT                  LATAbits.LATA6
#define led3_PORT                 PORTAbits.RA6
#define led3_WPU                  WPUAbits.WPUA6
#define led3_OD                   ODCONAbits.ODCA6
#define led3_ANS                  ANSELAbits.ANSELA6
#define led3_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define led3_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define led3_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define led3_GetValue()           PORTAbits.RA6
#define led3_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define led3_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define led3_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define led3_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define led3_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define led3_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define led3_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define led3_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set led4 aliases
#define led4_TRIS                 TRISAbits.TRISA7
#define led4_LAT                  LATAbits.LATA7
#define led4_PORT                 PORTAbits.RA7
#define led4_WPU                  WPUAbits.WPUA7
#define led4_OD                   ODCONAbits.ODCA7
#define led4_ANS                  ANSELAbits.ANSELA7
#define led4_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define led4_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define led4_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define led4_GetValue()           PORTAbits.RA7
#define led4_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define led4_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define led4_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define led4_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define led4_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define led4_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define led4_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define led4_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()               do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()                do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()                do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()       do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()      do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set s1 aliases
#define s1_TRIS                 TRISBbits.TRISB4
#define s1_LAT                  LATBbits.LATB4
#define s1_PORT                 PORTBbits.RB4
#define s1_WPU                  WPUBbits.WPUB4
#define s1_OD                   ODCONBbits.ODCB4
#define s1_ANS                  ANSELBbits.ANSELB4
#define s1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define s1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define s1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define s1_GetValue()           PORTBbits.RB4
#define s1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define s1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define s1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define s1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define s1_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define s1_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define s1_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define s1_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()               do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()                do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()                do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()       do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()      do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()               do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()                do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()                do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()       do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()      do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()               do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()                do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()                do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()       do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()      do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set s2 aliases
#define s2_TRIS                 TRISCbits.TRISC5
#define s2_LAT                  LATCbits.LATC5
#define s2_PORT                 PORTCbits.RC5
#define s2_WPU                  WPUCbits.WPUC5
#define s2_OD                   ODCONCbits.ODCC5
#define s2_ANS                  ANSELCbits.ANSELC5
#define s2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define s2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define s2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define s2_GetValue()           PORTCbits.RC5
#define s2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define s2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define s2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define s2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define s2_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define s2_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define s2_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define s2_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()               do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()                do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()                do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()       do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()      do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/