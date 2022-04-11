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
		*vectorOut++ = (*vectorIn++ * escalar) & 0x0FFF;
	}
}


