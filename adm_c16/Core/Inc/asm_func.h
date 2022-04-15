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
