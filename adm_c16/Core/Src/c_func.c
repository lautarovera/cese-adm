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

void zeros(uint32_t *vector, uint32_t longitud)
{
	/* Se podría implementar directamente con memset(vector, 0, longitud * 4u) */
	for (;vector < (&vector[0u] + longitud); vector++) {
		*vector = 0u;
	}
}

void productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar)
{
	uint32_t tmp = 0u;

	for (;vectorIn < (&vectorIn[0u] + longitud); vectorIn++) {
		tmp = *vectorIn * escalar;
		*vectorOut++ = tmp;
	}
}

void productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar)
{
	uint16_t tmp = 0u;

	for (;vectorIn < (&vectorIn[0u] + longitud); vectorIn++) {
		tmp = *vectorIn * escalar;
		*vectorOut++ = tmp;
	}
}

void productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar)
{
	uint16_t tmp = 0u;

	for (;vectorIn < (&vectorIn[0u] + longitud); vectorIn++) {
		tmp = (*vectorIn * escalar) ;
		/* Haciendo tmp &= 0x0FFF se logra overflow a 12 bits, no saturación */
		tmp = tmp > 0x0FFF ? 0x0FFF : tmp;
		*vectorOut++ = tmp;
	}
}


