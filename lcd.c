/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

#include "lcd.h"
/*

void Lcd_Port(char a)
{
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char a)
{
    RS = 0;
    Lcd_Port(a);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

void Lcd_Clear(void) {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init(void) {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_us(11);
    Lcd_Cmd(0x03);
    ///////////////////////////////////////////////////// 
    Lcd_Cmd(0x02);  // 4 bits
    
    Lcd_Cmd(0x02);  // 4 bits
    Lcd_Cmd(0x08);  // 2 lines
    
    
    Lcd_Cmd(0x00);  // 4 bits visualizador apagado cursor apagado sin blinkeo
    Lcd_Cmd(0x0C);
    
    
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a) {
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1;
    Lcd_Port(y >> 4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}

*/

// 8 bits

void Lcd_Cmd_8(char a)
{
    RS = 0;
    Lcd_Port_8(a);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

void Lcd_Port_8(char a)
{
    if (a & 1)
        D0 = 1;
    else
        D0 = 0;

    if (a & 2)
        D1 = 1;
    else
        D1 = 0;

    if (a & 4)
        D2 = 1;
    else
        D2 = 0;

    if (a & 8)
        D3 = 1;
    else
        D3 = 0;

    if (a & 16)
        D4 = 1;
    else
        D4 = 0;

    if (a & 32)
        D5 = 1;
    else
        D5 = 0;

    if (a & 64)
        D6 = 1;
    else
        D6 = 0;

    if (a & 128)
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Init_8(void) {
    Lcd_Port_8(0x00);
    __delay_ms(20);
    Lcd_Cmd_8(0x03);
    __delay_ms(5);
    Lcd_Cmd_8(0x03);
    __delay_us(11);
    Lcd_Cmd_8(0x03);
    ///////////////////////////////////////////////////// 
    Lcd_Cmd_8(0x03);
    
    Lcd_Cmd_8(0x38);        // 8 bits  y 2 lineas
    
    Lcd_Cmd_8(0x0C);        // Visualizador apagado cursor apagado sin blinkeo
    
    Lcd_Cmd_8(0x06);        // incremento y desplazamiento desactivado
}

void Lcd_Clear_8(void) {
    Lcd_Cmd_8(0x01);
}

void Lcd_Set_Cursor_8(char a, char b)
{
     char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd_8(temp);
        z = temp >> 4;
        y = temp & 0x0F;
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd_8(temp);
        z = temp >> 4;
        y = temp & 0x0F;
    }
}

void Lcd_Write_Char_8(char a) {
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1;
    Lcd_Port_8(a);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Shift_Right_8(void) {
    Lcd_Cmd_8(0x1C);
}

void Lcd_Shift_Left_8(void) {
    Lcd_Cmd_8(0x18);
}

void Lcd_Write_String_8(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char_8(a[i]);
}