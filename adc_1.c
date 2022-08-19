#include <xc.h>
#include "adc_1.h"
#define _XTAL_FREQ 4000000

void adc_init (uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus){
    switch(adc_cs){                        // Switch case para indicar frecuencia de oscilador
        case 0:
            ADCON0bits.ADCS = 0b00;         // FOSC/2
            break;
        case 1:
            ADCON0bits.ADCS = 0b01;         // FOSC/8
            break;
        case 2:
            ADCON0bits.ADCS = 0b10;         // FOSC/32
            break;
        case 3:
            ADCON0bits.ADCS = 0b11;         // FRC
            break;
        default:
            break;
    }
    ADCON1bits.VCFG0 = vref_plus;       // VDD
    ADCON1bits.VCFG1 = vref_minus;       // VSS
    ADCON0bits.CHS = 0b0000;    // Seleccionamos el AN0
    ADCON1bits.ADFM = 0;        // Justificado a la izquierda
    ADCON0bits.ADON = 1;        // Habilitamos modulo ADC
    __delay_us(40);             // Sample time
}

void adc_start(uint8_t channel){
    if(channel < 14){
        ADCON0bits.CHS = channel;
    }
    else{
        ADCON0bits.CHS = 0; //canal 0 default
    }
    __delay_us(40);             // Sample time
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO){}
}

uint16_t adc_read(void){
    PIR1bits.ADIF = 0;          // Limpiamos bandera de ADC
    return (ADRESH);            //Retorna lectura de ADC en ADRESH
}
