/*
 * configuracion.hpp
 *
 *  Created on: May 13, 2018
 *      Author: daniel
 */

#ifndef CONFIGURACION_HPP_
#define CONFIGURACION_HPP_

#include <msp.h>

/**
 * Configuración del ADC
 *
 * Reloj MCLK (48 MHz)
 *
 * Predivisor:
 *      1 | 4 | [32] | 64 *
 * Divisor:
 *      1 | [2] | 3 | 4 | 5 | 6 | 7
 *
 *  --> Reloj ADC = 750 kHz
 *
 *  ADC14SHT0x (ciclos para muestreo):
 *      4 | 8 | 16 | 32 | [64] | 96 | 128 | 192
 *
 * ---> Periodo de muestreo = 85 us (11.718 kHz)
 * ---> Tiempo total de conversión = 116 us exactos (87 ciclos, 8.620 kHz)
 *
 *  Pulse Sample Mode
 *  Sequence of channels Mode (3 valores del acelerómetro)
 *  ADC14->MEM[0:2]
 */
void ConfigADC();

/**
 * Definir puertos del acelerómetro como entrada.
 *
 * (P6.1, P4.0, P4.2) = (x, y, z)
 */
void ConfigAccel();


#endif /* CONFIGURACION_HPP_ */
