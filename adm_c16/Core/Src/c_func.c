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
	uint32_t res = 0u;
	uint16_t *init_pos = vectorIn;
	uint16_t *filt_pos = init_pos;
	uint32_t l = longitud;

	while (l--) {
		filt_pos = (filt_pos > (init_pos + longitud)) ? init_pos : filt_pos;
		res += *vectorIn++;

		if (vectorIn >= (filt_pos + 10u)) {
			res /= 10u;
			*vectorOut++ = (uint16_t)res;
			vectorIn = ++filt_pos;
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
		vectorIn++;
	}

	return max;
}

void downsampleN(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, uint32_t N)
{
	uint32_t n = 0u;

	while (longitud--) {
		if (n++ < N) {
			*vectorOut++ = *vectorIn++;
		}
		else {
			n = 0u;
			vectorIn++;
		}
	}
}

void invertir(uint16_t *vectorIn, uint32_t longitud)
{
//	uint32_t n = longitud;
//	uint16_t tmp[longitud];
//	uint16_t *tmp_ptr = &tmp[0u];
//
//	while (n--) {
//		*tmp_ptr++ = vectorIn[n];
//	}
//
//	n = longitud;
//	tmp_ptr = &tmp[0u];
//
//	while (n--) {
//		*vectorIn++ = *tmp_ptr++;
//	}
	uint16_t tmp = 0u;

	for (uint32_t l = 0u, h = (longitud - 1u); l < h; l++, h--)
	{
		tmp = vectorIn[l];
		vectorIn[l] = vectorIn[h];
		vectorIn[h] = tmp;
	}

}
