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
 * @brief Función que inicializa un vector con un valor escalar de 32 bits.
 * @param[in] vector   : Vector a inicializar con ceros.
 * @param[in] longitud : Longitud del vector a inicializar con ceros.
 * @param[in] escalar  : Escalar de inicialización.
 */
void asignarEscalar32(uint32_t *vector, uint32_t longitud, uint32_t escalar);

/**
 * @brief Función que inicializa un vector con un valor escalar de 16 bits.
 * @param[in] vector   : Vector a inicializar con ceros.
 * @param[in] longitud : Longitud del vector a inicializar con ceros.
 * @param[in] escalar  : Escalar de inicialización.
 */
void asignarEscalar16(uint16_t *vector, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que inicializa un vector con ceros.
 * @param[in] vector   : Vector a inicializar con ceros.
 * @param[in] longitud : Longitud del vector a inicializar con ceros.
 */
void zeros(uint32_t *vector, uint32_t longitud);

/**
 * @brief Función que realiza el producto de un vector de 32 bits por un escalar de 32 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar);

/**
 * @brief Función que realiza el producto de un vector de 16 bits por un escalar de 16 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que realiza el producto de un vector de 16 bits por un escalar de 16 bits,
 * pero recortando el resultado a 12 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto de 12 bits.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que realiza el producto de un vector de 16 bits por un escalar de 16 bits,
 * pero saturando el resultado a 12 bits.
 * @param[in]  vectorIn  : Vector de entrada como operando del producto.
 * @param[out] vectorOut : Vector resultado del producto saturado a 12 bits.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  escalar   : Escalar como operando del producto
 */
void productoEscalar12Sat(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);

/**
 * @brief Función que implementa un filtro de ventana móvil de 10 valores sobre un vector de muestras,
 * haciendo rollover cuando la ventana supera el extremo del vector de entrada.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[out] vectorOut : Vector resultado del filtro de ventana, su longitud debe ser mayor o igual a longitudVectorIn.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 */
void filtroVentana10(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud);

/**
 * @brief Función que recibe un vector de muestras signadas de 32 bits y los empaqueta en otro vector
 * de 16 bits.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[out] vectorOut : Vector resultado del empaquetado.
 * @param[in]  longitud	 : Longitud del vector de entrada y del vector resultado.
 */
void pack32to16(int32_t *vectorIn, int16_t *vectorOut, uint32_t longitud);

/**
 * @brief Función que recibe un vector de muestras signadas de 32 bits y devuelve la posición del máximo
 * del vector.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[in]  longitud  : Longitud del vector de entrada.
 */
int32_t max(int32_t *vectorIn, uint32_t longitud);

/**
 * @brief Función que recibe un vector de muestras signadas de 32 bits y lo decima descartando
 * una de cada N muestras.
 * @param[in]  vectorIn  : Vector de muestras.
 * @param[out] vectorOut : Vector resultado de la decimación.
 * @param[in]  longitud  : Longitud del vector de entrada y del vector resultado.
 * @param[in]  N		 : Frecuencia de decimación.
 */
void downsampleN(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, uint32_t N);

/**
 * @brief Función que recibe un vector de muestras no signadas e invierte su orden.
 * @param[in]  vectorIn : Vector de muestras.
 * @param[in]  longitud : Longitud del vector de entrada.
 */
void invertir(uint16_t *vectorIn, uint32_t longitud);

#endif /* C_FUNC_H_ */
