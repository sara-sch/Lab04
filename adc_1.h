/* 
 * File:   adc.h
 * Author: saras
 *
 * Created on July 22, 2022, 11:14 AM
 */

#ifndef ADC_H
#define	ADC_H


#include <xc.h>
#include <stdint.h>

//Definimos funciones
void adc_init(uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus);
void adc_start(uint8_t channel);
uint16_t adc_read(void);
#endif	/* OSCILADOR_H */

