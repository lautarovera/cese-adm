/**
  ******************************************************************************
  * @file           : c_func.h
  * @brief          : Guía de Ejercicios ADM: Funciones en C
  ******************************************************************************
  * @author 		: Lautaro
  ******************************************************************************
  */

#ifndef C_FUNC_H_
#define C_FUNC_H_

/* Functions prototypes -----------------------------------------------------*/

/**
 * @brief Función que inicializa un vector con ceros.
 * Se podría implementar directamente con memset(vector, 0, longitud).
 * @param[in] vector   : Vector a inicializar con ceros.
 * @param[in] longitud : Longitud del vector a inicializar con ceros.
 */
void zeros(uint32_t *vector, uint32_t longitud);

/**
 * @brief Función que realiza el producto de un vector por un escalar.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar);

#endif /* C_FUNC_H_ */