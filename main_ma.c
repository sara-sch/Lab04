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
#include "lcd.h"

//Definición de variables
#define _XTAL_FREQ 4000000

uint8_t pot = 0;
uint8_t entero = 0;
uint8_t decimal = 0;

uint8_t hora = 5;                            
uint8_t minutos = 25;                          
uint8_t segundos = 15;                          

unsigned short voltaje = 0;
char s[];

//Definicion de funciones
void setup (void);

unsigned short map(uint8_t val, uint8_t in_min, uint8_t in_max, 
            unsigned short out_min, unsigned short out_max);

uint8_t BCD_decimal (uint8_t number);
uint8_t decimal_BCD (uint8_t number); 

void main(void){
    setup();
    
    segundos = decimal_BCD(segundos);
    minutos = decimal_BCD(minutos);
    hora = decimal_BCD(hora);

    I2C_Master_Start();                
    I2C_Master_Write(0xD0);            
    I2C_Master_Write(0x00);            
    I2C_Master_Write(segundos);            
    I2C_Master_Write(minutos);         
    I2C_Master_Write(hora);          
    I2C_Master_Stop();                 
    __delay_ms(200);            
    
    while (1){
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(PORTB);
        I2C_Master_Stop();
        __delay_ms(20);
       
        I2C_Master_Start();
        I2C_Master_Write(0x51); 
        pot = I2C_Master_Read(0);
        I2C_Master_Stop(); 
        __delay_ms(10); 
        
        voltaje = map(pot, 0, 255, 0, 500); 
        entero = voltaje/100; 
        decimal = voltaje-entero*100; 
        
        Lcd_Set_Cursor_8(1,1);
            Lcd_Write_String_8("POT");
            Lcd_Set_Cursor_8(2,1);
            sprintf(s, " %d.%d%dV ", entero, decimal/10, decimal%10); 
            Lcd_Set_Cursor_8(2,1);
            
            Lcd_Write_String_8(s);
    }
    return;
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISB = 1; 
    PORTB = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISE = 0;
    PORTE = 0;
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    int_osc_MHz(4);
    I2C_Master_Init(100000);
    Lcd_Init_8(); 
    Lcd_Clear_8(); 
}

unsigned short map(uint8_t x, uint8_t x0, uint8_t x1,
            unsigned short y0, unsigned short y1){
    return (unsigned short)(y0+((float)(y1-y0)/(x1-x0))*(x-x0));
}

uint8_t BCD_decimal (uint8_t number)           
{
  return ((number >> 4) * 10 + (number & 0x0F));  
}
uint8_t decimal_BCD (uint8_t number)            
{
    return (((number / 10) << 4) + (number % 10));
}