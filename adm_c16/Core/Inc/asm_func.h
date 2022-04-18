#pragma once

#include <stdint.h>


void asm_svc (void);

uint32_t asm_sum (uint32_t firstOperand, uint32_t secondOperand);

/**
 * @brief Función que inicializa un vector con ceros.
 * @param[in] vector   : Vector a inicializar con ceros.
 * @param[in] longitud : Longitud del vector a inicializar con ceros.
 */
void asm_zeros(uint32_t *vector, uint32_t longitud);

/**
 * @brief Función que realiza el producto de un vector de 32 bits por un escalar de 32 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void asm_productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar);

/**
 * @brief Función que realiza el producto de un vector de 16 bits por un escalar de 16 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void asm_productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que realiza el producto de un vector de 16 bits por un escalar de 16 bits,
 * pero restringiendo el resultado a 12 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto saturado a 12 bits.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void asm_productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que realiza el producto de un vector de 16 bits por un escalar de 16 bits,
 * pero saturando el resultado a 12 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto saturado a 12 bits.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void asm_productoEscalar12Sat(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que implementa un filtro de ventana móvil de 10 valores sobre un vector de muestras,
 * haciendo rollover cuando la ventana supera el extremo del vector de entrada.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[out] vectorOut : Vector resultado del filtro de ventana, su longitud debe ser mayor o igual a longitudVectorIn.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 */
void asm_filtroVentana10(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud);

/**
 * @brief Función que recibe un vector de muestras signadas de 32 bits y los empaqueta en otro vector
 * de 16 bits.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[out] vectorOut : Vector resultado del empaquetado.
 * @param[in]  longitud	 : Longitud del vector de entrada y del vector resultado.
 */
void asm_pack32to16(int32_t *vectorIn, int16_t *vectorOut, uint32_t longitud);

/**
 * @brief Función que recibe un vector de muestras signadas de 32 bits y devuelve la posición del máximo
 * del vector.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[in]  longitud  : Longitud del vector de entrada.
 */
int32_t asm_max(int32_t *vectorIn, uint32_t longitud);

/**
 * @brief Función que recibe un vector de muestras signadas de 32 bits y lo decima descartando
 * una de cada N muestras.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[out] vectorOut : Vector resultado de la decimación.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  N		 : Frecuencia de decimación.
 */
void asm_downsampleN(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, uint32_t N);

/**
 * @brief Función que recibe un vector de muestras no signadas e invierte su orden.
 * @param[in]  vectorIn : Vector de muestras.
 * @param[in]  longitud : Longitud del vector de entrada.
 */
void asm_invertir(uint16_t *vectorIn, uint32_t longitud);
