/* 
 * File:   mainl4.c
 * Author: saras
 *
 * Created on August 12, 2022, 10:41 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "I2C.h"
#include "oscilador_1.h"

//Definición de variables
#define _XTAL_FREQ 4000000
uint8_t z;
uint8_t dato;

//Definicion de funciones
void setup (void);

//interrupción 

void __interrupt() isr(void){
    if(PIR1bits.SSPIF == 1){
        SSPCONbits.CKP = 0; 
        
        if((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)) {
            z = SSPBUF;
            SSPCONbits.SSPOV = 0;       //read preview value to clear the buffer
            SSPCONbits.WCOL = 0;        //clear de overflow flag
            SSPCONbits.CKP = 1;         //clear the collisson bit
        }
        
        if (!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7)
            z = SSPBUF;
            //__delay_us(2)
            PIR1bits.SSPIF = 0;
            SSPCONbits.CKP = 1; 
            while(!SSPSTATbits.BF);
            PORTD = SSPBUF;
            __delay_us(250);
        }
        
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = PORTB;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
        
        PIR1bits.SSPIF = 0; 
        
    }
    
}

void main (void){
    setup();
    while(1){          
    }
    return;
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    //TRISB = 0;
    TRISD = 0xf0;
    
    //PORTB = 0;
    PORTD = 0;
    int_osc_MHz(4);
    I2C_Slave_Init(0x50);
}

