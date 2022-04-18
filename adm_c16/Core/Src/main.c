/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "asm_func.h"
#include "c_func.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	ZEROS,
	PRO_ESC_32,
	PRO_ESC_16,
	PRO_ESC_12,
	PRO_ESC_12_SAT,
	FIL_VEN_10,
	PCK_32_16,
	MAX,
	DOWNSAMPLE,
	INVERTIR,
	MAX_FUNC_NUM
} func_index_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LENGTH_BUFFER_UART		80u
#define LENGTH_BUFFER_IN_OUT	20u
#define DWT_ENABLE				1u
#define USE_FULL_ASSERT			1u
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#ifdef DWT_ENABLE
	#if DWT_ENABLE == 1u
		#define DWT_START()				(DWT->CYCCNT = 0u)
		#define DWT_STOP()				({uint32_t retval; retval = DWT->CYCCNT; retval;})
	#else
		#define DWT_START()
		#define DWT_STOP()
	#endif
#endif

void assert_failed(uint32_t line, uint32_t x, uint32_t y);

#ifdef USE_FULL_ASSERT
	#define ASSERT(x,y) 				if(x != y) {assert_failed(__LINE__, x, y);}
#endif
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;
UART_HandleTypeDef huart3;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

const char *func_names[MAX_FUNC_NUM] = {
		"zeros               ",
		"productoEscalar32   ",
		"productoEscalar16   ",
		"productoEscalar12   ",
		"productoEscalar12Sat",
		"filtroVentana10     ",
		"pack32to16          ",
		"max                 ",
		"downsampleN         ",
		"invertir            "
};
char buffer_uart[LENGTH_BUFFER_UART];
uint32_t buffer_zeros[LENGTH_BUFFER_IN_OUT] = {0xFFFFFFFFu};
uint32_t buffer_in_32[LENGTH_BUFFER_IN_OUT] = {5u, 3u, 16u, 255u, 65535u, 5u, 3u, 16u, 255u, 65535u, 5u, 3u, 16u, 255u, 65535u, 5u, 3u, 16u, 255u, 65535u};
uint32_t buffer_out_32[LENGTH_BUFFER_IN_OUT] = {0u};
uint16_t buffer_in_16[LENGTH_BUFFER_IN_OUT] = {0xFFFFu, 0xFFF0u, 0xFF00, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 0x0000u, 5u, 5u, 5u, 5u, 5u, 5u, 5u, 5u, 5u, 5u};
uint16_t buffer_out_16[LENGTH_BUFFER_IN_OUT] = {0u};
int32_t buffer_in_s32[LENGTH_BUFFER_IN_OUT] = {0xFFFFFFFFu, 0xFFF0u, 0xFF00, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 10u};
int32_t buffer_out_s32[LENGTH_BUFFER_IN_OUT] = {0u};
int16_t buffer_in_s16[LENGTH_BUFFER_IN_OUT] = {0xFFFFu, 0xFFF0u, 0xFF00, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 0x0000u, 0xFFFFu, 0xFFF0u, 0xFF00u, 0xF000u, 0x0000u};
int16_t buffer_out_s16[LENGTH_BUFFER_IN_OUT] = {0u};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void PrivilegiosSVC (void)
{
    // Obtiene valor del registro de 32 bits del procesador llamado "control".
    // El registro guarda los siguientes estados:
    // bit 2: Uso de FPU en el contexto actual. Usado=1, no usado=0.
    // bit 1: Mapeo del stack pointer(sp). MSP=0, PSP=1.
    // bit 0: Modo de ejecucion en Thread. Privilegiado=0, No privilegiado=1.
    //        Recordar que este valor solo se usa en modo Thread. Las
    //        interrupciones siempre se ejecutan en modo Handler con total
    //        privilegio.
    uint32_t x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    x |= 1;
    // bit 0 a modo No privilegiado.
    __set_CONTROL (x);

    // En este punto se estaria ejecutando en modo No privilegiado.
    // Lectura del registro "control" para confirmar.
    x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    x &= ~1u;
    // Se intenta volver a modo Privilegiado (bit 0, valor 0).
    __set_CONTROL (x);

    // Confirma que esta operacion es ignorada por estar ejecutandose en modo
    // Thread no privilegiado.
    x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    // En este punto, ejecutando en modo Thread no privilegiado, la unica forma
    // de volver a modo privilegiado o de realizar cualquier cambio que requiera
    // modo privilegiado, es pidiendo ese servicio a un hipotetico sistema
    // opertivo de tiempo real.
    // Para esto se invoca por software a la interrupcion SVC (Supervisor Call)
    // utilizando la instruccion "svc".
    // No hay intrinsics para realizar esta tarea. Para utilizar la instruccion
    // es necesario implementar una funcion en assembler. Ver el archivo
    // asm_func.S.
    asm_svc ();

    // El sistema operativo (el handler de SVC) deberia haber devuelto el modo
    // de ejecucion de Thread a privilegiado (bit 0 en valor 0).
    x = __get_CONTROL ();

    // Fin del ejemplo de SVC
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
	uint32_t res = 0u;
	volatile uint32_t clang_cyc_cnt[MAX_FUNC_NUM];
	volatile uint32_t assembly_cyc_cnt[MAX_FUNC_NUM];

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ETH_Init();
	MX_USART3_UART_Init();
	MX_USB_OTG_FS_PCD_Init();
	/* Habilita y activa el DWT */
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	CoreDebug->DEMCR |= 1ul << CoreDebug_DEMCR_MON_EN_Pos;
	ITM->LAR = 0xC5ACCE55;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

	/* USER CODE BEGIN 2 */
	/*********************************************************************
	 * Warm Up
	 *********************************************************************/
	#ifdef DWT_ENABLE
		#if DWT_ENABLE != 1u
			PrivilegiosSVC();
		#endif
	#endif
	res = asm_sum(5, 3);

	/*********************************************************************
	 * 1) Función "zeros": benchmark C vs assembly
	 *********************************************************************/
	DWT_START();
	zeros(buffer_zeros, LENGTH_BUFFER_IN_OUT);
	clang_cyc_cnt[ZEROS] = DWT_STOP();

	for(uint32_t i = 0u; i < LENGTH_BUFFER_IN_OUT; i++) {
		ASSERT(buffer_zeros[0u], 0u);
	}

	asignarEscalar32(buffer_zeros, LENGTH_BUFFER_IN_OUT, 0xFFFFFFFF);

	DWT_START();
	asm_zeros(buffer_zeros, LENGTH_BUFFER_IN_OUT);
	assembly_cyc_cnt[ZEROS] = DWT_STOP();

	for(uint32_t i = 0u; i < LENGTH_BUFFER_IN_OUT; i++) {
		ASSERT(buffer_zeros[0u], 0u);
	}

	/*********************************************************************
	 * 2) Función "productoEscalar32": benchmark C vs assembly
	 *********************************************************************/
	DWT_START();
	productoEscalar32(buffer_in_32, buffer_out_32, LENGTH_BUFFER_IN_OUT, 5u);
	clang_cyc_cnt[PRO_ESC_32] = DWT_STOP();

	ASSERT(buffer_out_32[0u], 25u);

	memset(buffer_out_32, 0, sizeof(buffer_out_32));

	DWT_START();
	asm_productoEscalar32(buffer_in_32, buffer_out_32, LENGTH_BUFFER_IN_OUT, 5u);
	assembly_cyc_cnt[PRO_ESC_32] = DWT_STOP();

	ASSERT(buffer_out_32[0u], 25u);

	/*********************************************************************
	 * 3) Función "productoEscalar16": benchmark C vs assembly
	 *********************************************************************/
	DWT_START();
	productoEscalar16(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT, 2u);
	clang_cyc_cnt[PRO_ESC_16] = DWT_STOP();

	ASSERT(buffer_out_16[LENGTH_BUFFER_IN_OUT - 1u], 10u);

	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	asm_productoEscalar16(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT, 2u);
	assembly_cyc_cnt[PRO_ESC_16] = DWT_STOP();

	ASSERT(buffer_out_16[LENGTH_BUFFER_IN_OUT - 1u], 10u);

	/*********************************************************************
	 * 4) Función "productoEscalar12": benchmark C vs assembly
	 *********************************************************************/
	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	productoEscalar12(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT, 1024u);
	clang_cyc_cnt[PRO_ESC_12] = DWT_STOP();

	ASSERT(buffer_out_16[LENGTH_BUFFER_IN_OUT - 1u], 1024u);
	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	asm_productoEscalar12(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT, 1024u);
	assembly_cyc_cnt[PRO_ESC_12] = DWT_STOP();

	ASSERT(buffer_out_16[LENGTH_BUFFER_IN_OUT - 1u], 1024u);

	/*********************************************************************
	 * 4-b) Función "productoEscalar12Sat": benchmark C vs assembly
	 *********************************************************************/
	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	productoEscalar12Sat(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT, 1024u);
	clang_cyc_cnt[PRO_ESC_12_SAT] = DWT_STOP();

	ASSERT(buffer_out_16[0u], 4095u);

	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	asm_productoEscalar12Sat(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT, 1024u);
	assembly_cyc_cnt[PRO_ESC_12_SAT] = DWT_STOP();

	ASSERT(buffer_out_16[0u], 4095u);

	/*********************************************************************
	 * 5) Función "filtroVentana10": benchmark C vs assembly
	 *********************************************************************/
	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	filtroVentana10(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT);
	clang_cyc_cnt[FIL_VEN_10] = DWT_STOP();

	ASSERT(buffer_out_16[0u], 51555u);

	memset(buffer_out_16, 0, sizeof(buffer_out_16));

	DWT_START();
	asm_filtroVentana10(buffer_in_16, buffer_out_16, LENGTH_BUFFER_IN_OUT);
	assembly_cyc_cnt[FIL_VEN_10] = DWT_STOP();

	ASSERT(buffer_out_16[0u], 51555u);

	/*********************************************************************
	 * 6) Función "pack32to16": benchmark C vs assembly
	 *********************************************************************/

	DWT_START();
	pack32to16(buffer_in_s32, buffer_out_s16, LENGTH_BUFFER_IN_OUT);
	clang_cyc_cnt[PCK_32_16] = DWT_STOP();

	ASSERT(buffer_out_s16[0u], (int16_t)0xFFFFu);

	memset(buffer_out_s16, 0, sizeof(buffer_out_s16));

	DWT_START();
	asm_pack32to16(buffer_in_s32, buffer_out_s16, LENGTH_BUFFER_IN_OUT);
	assembly_cyc_cnt[PCK_32_16] = DWT_STOP();

	ASSERT(buffer_out_s16[0u], (int16_t)0xFFFFu);

	/*********************************************************************
	 * 7) Función "max": benchmark C vs assembly
	 *********************************************************************/

	DWT_START();
	int32_t max_res = max(buffer_in_s32, LENGTH_BUFFER_IN_OUT);
	clang_cyc_cnt[MAX] = DWT_STOP();

	ASSERT(max_res, (int32_t)65535);

	DWT_START();
	max_res = asm_max(buffer_in_s32, LENGTH_BUFFER_IN_OUT);
	assembly_cyc_cnt[MAX] = DWT_STOP();

	ASSERT(max_res, (int32_t)65535);

	/*********************************************************************
	 * 8) Función "downsampleN": benchmark C vs assembly
	 *********************************************************************/

	memset(buffer_out_s32, 0, sizeof(buffer_out_s32));

	DWT_START();
	downsampleN(buffer_in_s32, buffer_out_s32, LENGTH_BUFFER_IN_OUT, 6u);
	clang_cyc_cnt[DOWNSAMPLE] = DWT_STOP();

	ASSERT(buffer_out_s32[3u], buffer_in_s32[3u]);
	ASSERT(buffer_out_s32[6u], buffer_in_s32[7u]);

	memset(buffer_out_s32, 0, sizeof(buffer_out_s32));

	DWT_START();
	asm_downsampleN(buffer_in_s32, buffer_out_s32, LENGTH_BUFFER_IN_OUT, 6u);
	assembly_cyc_cnt[DOWNSAMPLE] = DWT_STOP();

	ASSERT(buffer_out_s32[3u], buffer_in_s32[3u]);
	ASSERT(buffer_out_s32[6u], buffer_in_s32[7u]);

	/*********************************************************************
	 * 9) Función "invertir": benchmark C vs assembly
	 *********************************************************************/

	DWT_START();
	invertir(buffer_in_16, LENGTH_BUFFER_IN_OUT);
	clang_cyc_cnt[INVERTIR] = DWT_STOP();

	ASSERT(buffer_in_16[LENGTH_BUFFER_IN_OUT - 1], 0xFFFFu);

	DWT_START();
	asm_invertir(buffer_in_16, LENGTH_BUFFER_IN_OUT);
	assembly_cyc_cnt[INVERTIR] = DWT_STOP();

	ASSERT(buffer_in_16[0u], 0xFFFFu);

	/*********************************************************************
	 * Prints
	 *********************************************************************/
 	sprintf( buffer_uart, "Arquitectura de Microprocesadores - Guia de ejercicios\r\n\n" );
	HAL_UART_Transmit( &huart3, (uint8_t *)buffer_uart, (uint16_t) strlen((char *)buffer_uart), 10u );
	sprintf( buffer_uart, "Warm Up!\tasm_sum(5,3) = %lu\r\n\n", (uint32_t)res );
	HAL_UART_Transmit( &huart3, (uint8_t *)buffer_uart, (uint16_t) strlen((char *)buffer_uart), 10u );
	sprintf( buffer_uart, "Benchmark Ciclos C vs Assembly\r\n\nFuncion\t\t\t\tC\t     Assembly\r\n" );
	HAL_UART_Transmit( &huart3, (uint8_t *)buffer_uart, (uint16_t) strlen((char *)buffer_uart), 10u );
	sprintf( buffer_uart, "------------------------------------------------------\r\n" );
	HAL_UART_Transmit( &huart3, (uint8_t *)buffer_uart, (uint16_t) strlen((char *)buffer_uart), 10u );

	for (func_index_t func_index = ZEROS; func_index < MAX_FUNC_NUM; func_index++) {
		sprintf( buffer_uart, "%s\t%10ld\t\%10ld\r\n", func_names[func_index], clang_cyc_cnt[func_index], assembly_cyc_cnt[func_index] );
		HAL_UART_Transmit( &huart3, (uint8_t *)buffer_uart, (uint16_t) strlen((char *)buffer_uart), 10u );
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint32_t line, uint32_t x, uint32_t y)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number */
     sprintf(buffer_uart, "Error linea %ld: se espera %lX, devuelve %lX\r\n", (line - 3u), y, x);
     HAL_UART_Transmit( &huart3, (uint8_t *)buffer_uart, (uint16_t) strlen((char *)buffer_uart), 10u );
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
