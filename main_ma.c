/* 
 * File:   main_sl.c
 * Author: saras
 *
 * Created on August 12, 2022, 11:20 AM
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
#include "tmr0.h"
#include "oscilador_1.h"

//Definición de variables
#define _XTAL_FREQ 4000000

uint8_t cont = 0;
uint8_t cont2 = 0;
uint8_t send = 0;

//Definicion de funciones
void setup (void);


void __interrupt() isr (void){  
    if(INTCONbits.T0IF){
            cont++;
            if (cont == 18){
                cont = 0; 
                cont2++; 
            }
            PORTB = cont2;
    }
    tmr0_reload();
    return;
}


void main(void){
    setup();
    while (1){
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(cont2);
        I2C_Master_Stop();
        __delay_ms(20);
       
//        I2C_Master_Start();
//        I2C_Master_Write(0x51);
//        PORTD = I2C_Master_Read(0);
//        I2C_Master_Stop();
//        __delay_ms(200);
//        PORTB++;  
    }
    return;
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISB = 0x0f;
    PORTB = 0;
    
    INTCONbits.T0IE = 1;        // Habiltamos interrupciones
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    int_osc_MHz(4);
    I2C_Master_Init(100000);
    tmr0_init(256);  
}