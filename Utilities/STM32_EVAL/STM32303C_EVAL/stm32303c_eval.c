/**
  ******************************************************************************
  * @file    stm32303c_eval.c
  * @author  MCD Application Team
  * @version V1.0.4
  * @date    15-December-2021
  * @brief   This file provides firmware functions to manage Leds, push-buttons, 
  *          COM ports, SD card on SPI and temperature sensor (TS751) available on 
  *          STM32303C-EVAL evaluation board from STMicroelectronics.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32303c_eval.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM32303C_EVAL
  * @{
  */   
    
/** @defgroup STM32303C_EVAL_LOW_LEVEL 
  * @brief This file provides firmware functions to manage Leds, push-buttons, 
  *        COM ports, SD card on SPI and temperature sensor (TS751) available on 
  *        STM32303C-EVAL evaluation board from STMicroelectronics.
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/ 
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN,
                                 LED4_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK,
                                 LED4_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {KEY_BUTTON_GPIO_PORT, RIGHT_BUTTON_GPIO_PORT,
                                      LEFT_BUTTON_GPIO_PORT, UP_BUTTON_GPIO_PORT, 
                                      DOWN_BUTTON_GPIO_PORT, SEL_BUTTON_GPIO_PORT}; 

const uint16_t BUTTON_PIN[BUTTONn] = {KEY_BUTTON_PIN, RIGHT_BUTTON_PIN, LEFT_BUTTON_PIN, 
                                      UP_BUTTON_PIN, DOWN_BUTTON_PIN, SEL_BUTTON_PIN}; 

const uint32_t BUTTON_CLK[BUTTONn] = {KEY_BUTTON_GPIO_CLK, RIGHT_BUTTON_GPIO_CLK,
                                      LEFT_BUTTON_GPIO_CLK, UP_BUTTON_GPIO_CLK, 
                                      DOWN_BUTTON_GPIO_CLK, SEL_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {KEY_BUTTON_EXTI_LINE,
                                            RIGHT_BUTTON_EXTI_LINE,
                                            LEFT_BUTTON_EXTI_LINE,
                                            UP_BUTTON_EXTI_LINE,
                                            DOWN_BUTTON_EXTI_LINE,
                                            SEL_BUTTON_EXTI_LINE};

const uint8_t BUTTON_PORT_SOURCE[BUTTONn] = {KEY_BUTTON_EXTI_PORT_SOURCE,
                                              RIGHT_BUTTON_EXTI_PORT_SOURCE,
                                              LEFT_BUTTON_EXTI_PORT_SOURCE,
                                              UP_BUTTON_EXTI_PORT_SOURCE,
                                              DOWN_BUTTON_EXTI_PORT_SOURCE,
                                              SEL_BUTTON_EXTI_PORT_SOURCE};
								 
const uint8_t BUTTON_PIN_SOURCE[BUTTONn] = {KEY_BUTTON_EXTI_PIN_SOURCE,
                                             RIGHT_BUTTON_EXTI_PIN_SOURCE,
                                             LEFT_BUTTON_EXTI_PIN_SOURCE,
                                             UP_BUTTON_EXTI_PIN_SOURCE,
                                             DOWN_BUTTON_EXTI_PIN_SOURCE,
                                             SEL_BUTTON_EXTI_PIN_SOURCE}; 

const uint8_t BUTTON_IRQn[BUTTONn] = {KEY_BUTTON_EXTI_IRQn, 
                                       RIGHT_BUTTON_EXTI_IRQn, LEFT_BUTTON_EXTI_IRQn, 
                                       UP_BUTTON_EXTI_IRQn, DOWN_BUTTON_EXTI_IRQn, 
                                       SEL_BUTTON_EXTI_IRQn};

USART_TypeDef* COM_USART[COMn] = {EVAL_COM1}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT};

const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};
 
const uint16_t COM_TX_PIN_SOURCE[COMn] = {EVAL_COM1_TX_SOURCE};

const uint16_t COM_RX_PIN_SOURCE[COMn] = {EVAL_COM1_RX_SOURCE};
 
const uint8_t COM_TX_AF[COMn] = {EVAL_COM1_TX_AF};
 
const uint8_t COM_RX_AF[COMn] = {EVAL_COM1_RX_AF};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32303C_EVAL_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void STM_EVAL_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Led], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void STM_EVAL_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void STM_EVAL_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void STM_EVAL_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters: 
  *     @arg BUTTON_KEY: Key Push Button 
  *     @arg BUTTON_RIGHT: Joystick Right Push Button 
  *     @arg BUTTON_LEFT: Joystick Left Push Button 
  *     @arg BUTTON_UP: Joystick Up Push Button 
  *     @arg BUTTON_DOWN: Joystick Down Push Button
  *     @arg BUTTON_SEL: Joystick Sel Push Button
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  * @retval None
  */
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* There is no Wakeup button on STM32303C-EVAL, the Button value should
     be greater than 0. */
  if(Button > 0)
  {
    Button = (Button_TypeDef) (Button - 1);
    
    /* Enable the BUTTON Clock */
    RCC_AHBPeriphClockCmd(BUTTON_CLK[Button], ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Configure Button pin as input */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
    GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);


    if (Button_Mode == BUTTON_MODE_EXTI)
    {
      /* Connect Button EXTI Line to Button GPIO Pin */
      SYSCFG_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

      /* Configure Button EXTI line */
      EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    
      if(Button != BUTTON_KEY) 
      {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
      }
      else
      {
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
      }
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;
      EXTI_Init(&EXTI_InitStructure);

      /* Enable and set Button EXTI Interrupt to the lowest priority */
      NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

      NVIC_Init(&NVIC_InitStructure); 
    }
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON_KEY: Key Push Button 
  *     @arg BUTTON_RIGHT: Joystick Right Push Button 
  *     @arg BUTTON_LEFT: Joystick Left Push Button 
  *     @arg BUTTON_UP: Joystick Up Push Button 
  *     @arg BUTTON_DOWN: Joystick Down Push Button
  *     @arg BUTTON_SEL: Joystick Sel Push Button     
  * @retval - When Button > 0, the Button GPIO pin value is returned.
  *         - When Button = 0 , error code (0xFF) is returned.   
  */
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button)
{
  /* There is no Wakeup button on STM32303C_EVAL, the Button value should
     be greater than 0. */
  if(Button > 0)
  {
    Button = (Button_TypeDef) (Button - 1);
    return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
  }
  else
  {
    return 0xFF; /* Error Code */
  }
}

/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *   This parameter can be one of following parameters:    
  *     @arg COM1  
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *   contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 

  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);
    
  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}

/**
  * @brief  DeInitializes the SPI interface.
  * @param  None
  * @retval None
  */
void SD_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* SD_SPI disable */
  SPI_Cmd(SD_SPI, DISABLE); 
  
  /* DeInitializes the SD_SPI */
  SPI_I2S_DeInit(SD_SPI);   
  
  /* SD_SPI Periph clock disable */
  RCC_APB1PeriphClockCmd(SD_SPI_CLK, DISABLE); 

  /*Configure SD_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = SD_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(SD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = SD_SPI_MISO_PIN;
  GPIO_Init(SD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = SD_SPI_MOSI_PIN;
  GPIO_Init(SD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI_CS_PIN pin: SD Card CS pin */
  GPIO_InitStructure.GPIO_Pin = SD_CS_PIN;
  GPIO_Init(SD_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI_DETECT_PIN pin: SD Card detect pin */
  GPIO_InitStructure.GPIO_Pin = SD_DETECT_PIN;
  GPIO_Init(SD_DETECT_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the SPI and GPIOs resources used to drive the uSD card
  * @param  None
  * @retval None
  */
void SD_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /* SD_SPI_CS_GPIO, SD_SPI_MOSI_GPIO, SD_SPI_MISO_GPIO, SD_SPI_DETECT_GPIO 
       and SD_SPI_SCK_GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(SD_CS_GPIO_CLK | SD_SPI_MOSI_GPIO_CLK | SD_SPI_MISO_GPIO_CLK |
                        SD_SPI_SCK_GPIO_CLK | SD_DETECT_GPIO_CLK, ENABLE);

  /* SD_SPI Periph clock enable */
  RCC_APB1PeriphClockCmd(SD_SPI_CLK, ENABLE); 

  /* Configure SD_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = SD_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(SD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = SD_SPI_MISO_PIN;
  GPIO_Init(SD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = SD_SPI_MOSI_PIN;
  GPIO_Init(SD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI_CS_PIN pin: SD Card CS pin */
  GPIO_InitStructure.GPIO_Pin = SD_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SD_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SD_SPI_DETECT_PIN pin: SD Card detect pin */
  GPIO_InitStructure.GPIO_Pin = SD_DETECT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SD_DETECT_GPIO_PORT, &GPIO_InitStructure);

  /* Connect PXx to SD_SPI_SCK */
  GPIO_PinAFConfig(SD_SPI_SCK_GPIO_PORT, SD_SPI_SCK_SOURCE, SD_SPI_SCK_AF);

  /* Connect PXx to SD_SPI_MISO */
  GPIO_PinAFConfig(SD_SPI_MISO_GPIO_PORT, SD_SPI_MISO_SOURCE, SD_SPI_MISO_AF); 

  /* Connect PXx to SD_SPI_MOSI */
  GPIO_PinAFConfig(SD_SPI_MOSI_GPIO_PORT, SD_SPI_MOSI_SOURCE, SD_SPI_MOSI_AF);  
  
  /* SD_SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SD_SPI, &SPI_InitStructure);
  
  SPI_RxFIFOThresholdConfig(SD_SPI, SPI_RxFIFOThreshold_QF);
  
  /* SD_SPI enable */
  SPI_Cmd(SD_SPI, ENABLE); 
}

/**
  * @brief  DeInitializes the TS751_I2C.
  * @param  None
  * @retval None
  */
void TS751_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Disable TS751_I2C */
  I2C_Cmd(TS751_I2C, DISABLE);
  
  /* DeInitializes the TS751_I2C */
  I2C_DeInit(TS751_I2C);
  
  /* TS751_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(TS751_I2C_CLK, DISABLE);
    
  /* Configure TS751_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = TS751_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TS751_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure TS751_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = TS751_I2C_SDA_PIN;
  GPIO_Init(TS751_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

  /* Configure TS751_I2C pin: SMBUS ALERT */
  GPIO_InitStructure.GPIO_Pin = TS751_I2C_SMBUSALERT_PIN;
  GPIO_Init(TS751_I2C_SMBUSALERT_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the I2C source clock and IOs used to drive the TS751
  * @param  None
  * @retval None
  */
void TS751_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* TS751_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(TS751_I2C_CLK, ENABLE);
    
  /* Configure the I2C clock source. The clock is derived from the SYSCLK */
  RCC_I2CCLKConfig(RCC_I2C2CLK_SYSCLK);
  
  /* TS751_I2C_SCL_GPIO_CLK, TS751_I2C_SDA_GPIO_CLK 
       and TS751_I2C_SMBUSALERT_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(TS751_I2C_SCL_GPIO_CLK | TS751_I2C_SDA_GPIO_CLK |
                        TS751_I2C_SMBUSALERT_GPIO_CLK, ENABLE);
  
  /* Connect PXx to I2C_SCL */
  GPIO_PinAFConfig(TS751_I2C_SCL_GPIO_PORT, TS751_I2C_SCL_SOURCE, TS751_I2C_SCL_AF);

  /* Connect PXx to I2C_SDA */
  GPIO_PinAFConfig(TS751_I2C_SDA_GPIO_PORT, TS751_I2C_SDA_SOURCE, TS751_I2C_SDA_AF); 

  /* Connect PXx to I2C_SMBUSALERT */
  GPIO_PinAFConfig(TS751_I2C_SMBUSALERT_GPIO_PORT, TS751_I2C_SMBUSALERT_SOURCE, TS751_I2C_SMBUSALERT_AF);
    
  /* Configure TS751_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = TS751_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(TS751_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure TS751_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = TS751_I2C_SDA_PIN;
  GPIO_Init(TS751_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

  /* Configure TS751_I2C pin: SMBUS ALERT */
  GPIO_InitStructure.GPIO_Pin = TS751_I2C_SMBUSALERT_PIN;
  GPIO_Init(TS751_I2C_SMBUSALERT_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  DeInitializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void sEE_I2C_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
   
  /* sEE_I2C Peripheral Disable */
  I2C_Cmd(sEE_I2C, DISABLE);
 
  /* sEE_I2C DeInit */
  I2C_DeInit(sEE_I2C);

  /* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(sEE_I2C_CLK, DISABLE);
    
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sEE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
  GPIO_Init(sEE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the I2C source clock and IOs used to drive the EEPROM.
  * @param  None
  * @retval None
  */
void sEE_I2C_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Configure the I2C clock source. The clock is derived from the SYSCLK */
  RCC_I2CCLKConfig(RCC_I2C2CLK_SYSCLK);
    
  /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(sEE_I2C_SCL_GPIO_CLK | sEE_I2C_SDA_GPIO_CLK, ENABLE);
  
  /* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(sEE_I2C_CLK, ENABLE);
  
  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(sEE_I2C_SCL_GPIO_PORT, sEE_I2C_SCL_SOURCE, sEE_I2C_SCL_AF);
  
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(sEE_I2C_SDA_GPIO_PORT, sEE_I2C_SDA_SOURCE, sEE_I2C_SDA_AF);
  
  /* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_Init(sEE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
  GPIO_Init(sEE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);     
}

/**
  * @brief  DeInitializes the SPI interface.
  * @param  None
  * @retval None
  */
void sEE_SPI_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* sEE_SPI disable */
  SPI_Cmd(sEE_SPI, DISABLE); 
  
  /* DeInitializes the sEE_SPI */
  SPI_I2S_DeInit(sEE_SPI);   
  
  /* sEE_SPI Periph clock disable */
  RCC_APB1PeriphClockCmd(sEE_SPI_CLK, DISABLE); 

  /* Configure sEE_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sEE_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE pins: MISO */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_MISO_PIN;
  GPIO_Init(sEE_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_MOSI_PIN;
  GPIO_Init(sEE_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_CS_PIN pin: sEE Card CS pin */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_CS_PIN;
  GPIO_Init(sEE_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the SPI interface for EEPROM
  * @param  None
  * @retval None
  */
void sEE_SPI_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /* sEE_CS_GPIO, sEE_MOSI_GPIO, sEE_MISO_GPIO and sEE_SCK_GPIO 
     Periph clock enable */
  RCC_AHBPeriphClockCmd(sEE_SPI_CS_GPIO_CLK | sEE_SPI_MOSI_GPIO_CLK | sEE_SPI_MISO_GPIO_CLK |
                        sEE_SPI_SCK_GPIO_CLK , ENABLE);

  /* sEE Periph clock enable */
  RCC_APB1PeriphClockCmd(sEE_SPI_CLK, ENABLE); 

  /* Configure sEE pins: SCK */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(sEE_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE pins: MISO */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_MISO_PIN;
  GPIO_Init(sEE_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_MOSI_PIN;
  GPIO_Init(sEE_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_CS_PIN pin: sEE Card CS pin */
  GPIO_InitStructure.GPIO_Pin = sEE_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(sEE_SPI_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Connect PXx to sEE_SCK */
  GPIO_PinAFConfig(sEE_SPI_SCK_GPIO_PORT, sEE_SPI_SCK_SOURCE, sEE_SPI_SCK_AF);

  /* Connect PXx to sEE_MISO */
  GPIO_PinAFConfig(sEE_SPI_MISO_GPIO_PORT, sEE_SPI_MISO_SOURCE, sEE_SPI_MISO_AF); 

  /* Connect PXx to sEE_MOSI */
  GPIO_PinAFConfig(sEE_SPI_MOSI_GPIO_PORT, sEE_SPI_MOSI_SOURCE, sEE_SPI_MOSI_AF);  
  
  /* sEE SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sEE_SPI, &SPI_InitStructure);

  SPI_RxFIFOThresholdConfig(sEE_SPI, SPI_RxFIFOThreshold_QF);

  /* sEE_SPI enable */
  SPI_Cmd(sEE_SPI, ENABLE); 
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

