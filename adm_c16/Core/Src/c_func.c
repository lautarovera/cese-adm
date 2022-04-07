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

/* Función que inicializa un vector con ceros.
 * Se podría implementar directamente con memset(vector, 0, longitud).
 */
void zeros(uint32_t *vector, uint32_t longitud)
{
	for (;vector < (&vector[0u] + longitud); vector++) {
		*vector = 0u;
	}
}


