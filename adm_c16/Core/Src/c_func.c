/**
  ******************************************************************************
  * @file           : c_func.c
  * @brief          : Guía de Ejercicios ADM: Funciones en C
  ******************************************************************************
  * @author 		: Lautaro
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/

#include "c_func.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Functions definitions -----------------------------------------------------*/

void asignarEscalar32(uint32_t *vector, uint32_t longitud, uint32_t escalar)
{
	while (longitud--) {
		*vector++ = escalar;
	}
}

void asignarEscalar16(uint16_t *vector, uint16_t longitud, uint16_t escalar)
{
	while (longitud--) {
		*vector++ = escalar;
	}
}

void zeros(uint32_t *vector, uint32_t longitud)
{
	while (longitud--) {
		*vector++ = 0u;
	}
}

void productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar)
{
	while (longitud--) {
		*vectorOut++ = *vectorIn++ * escalar;
	}
}

void productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar)
{
	while (longitud--) {
		*vectorOut++ = *vectorIn++ * escalar;
	}
}

void productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar)
{
	while (longitud--) {
		*vectorOut++ = (*vectorIn++ * escalar) & 0xFFF;
	}
}

void productoEscalar12Sat(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar)
{
	uint16_t producto = 0u;

	while (longitud--) {
		producto = *vectorIn++ * escalar;
		*vectorOut++ = (producto > 0xFFF) ? 0xFFF : producto;
	}
}

void filtroVentana10(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud)
{
	uint16_t res = 0u;
	uint32_t filt_pos;
	uint32_t l = longitud;

	while (l--) {
		filt_pos = (uint32_t)vectorIn % ((uint32_t)&vectorIn[0u] + longitud);
		res += *vectorIn++;

		if ((uint32_t)vectorIn >= (filt_pos + 10u)) {
			res /= 10u;
			*vectorOut++ = res;
			vectorIn = (uint16_t *)filt_pos + 1u;
		}
	}
}

void pack32to16(int32_t *vectorIn, int16_t *vectorOut, uint32_t longitud)
{
	while (longitud--) {
		*vectorOut++ = *vectorIn++ >> 16u;
	}
}

int32_t max(int32_t *vectorIn, uint32_t longitud)
{
	int32_t max = 0x80000000u;

	while (longitud--) {
		max = (*vectorIn > max) ? *vectorIn : max;
	}

	return max;
}

void downsampleN(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, uint32_t N)
{
	uint32_t n = 0u;

	while (longitud--) {
		*vectorOut++ = (n++ < 10) ? *vectorIn++ : *(vectorIn + 2u);
		n %= N;
	}
}

void invertir(uint16_t *vectorIn, uint32_t longitud)
{
	uint16_t invertido = 0u;

	while (longitud--) {
		invertido = *(vectorIn + longitud);
		*vectorIn++ = invertido;
	}
}
