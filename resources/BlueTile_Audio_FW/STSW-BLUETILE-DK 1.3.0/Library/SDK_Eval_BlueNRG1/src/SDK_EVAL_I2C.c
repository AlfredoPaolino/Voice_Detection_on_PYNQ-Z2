/**
 * @file    SDK_EVAL_I2C.c
 * @author  AMS VMA RF application team
 * @version V1.0.0
 * @date    September 29, 2015
 * @brief   This file provides all the low level API to manage I2C interface for eval board.
 * @details
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
 * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
 *
 * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
 */


/* Includes ------------------------------------------------------------------*/
#include "SDK_EVAL_I2C.h"


/** @addtogroup SDK_EVAL_BlueNRG1         SDK EVAL BlueNRG1
 * @{
 */


/** @addtogroup SDK_EVAL_I2C            SDK EVAL I2C
 * @{
 */

/** @defgroup SDK_EVAL_I2C_Private_TypesDefinitions             SDK EVAL I2C Private Types Definitions
 * @{
 */

/**
 * @}
 */


/** @defgroup SDK_EVAL_I2C_Private_Defines                      SDK EVAL I2C Private Defines
 * @{
 */

/**
 * @brief  I2C DR address
 */
#define I2C_TX_DR_BASE_ADDR                (SDK_EVAL_I2C_BASE + 0x10)

#define I2C_RX_DR_BASE_ADDR                (SDK_EVAL_I2C_BASE + 0x18)


/**
 * @}
 */


/** @defgroup SDK_EVAL_I2C_Private_Macros                       SDK EVAL I2C Private Macros
 * @{
 */

/**
 * @}
 */


/** @defgroup SDK_EVAL_I2C_Private_Variable               SDK EVAL I2C Private Variable
 * @{
 */

/**
 * @brief  I2C buffers used for DMA application
 */
uint8_t i2c_buffer_tx[I2C_BUFF_SIZE];
uint8_t i2c_buffer_rx[I2C_BUFF_SIZE];

/**
 * @brief  I2C flag set at end of transaction
 */
volatile FlagStatus i2c_eot = SET;


/**
 * @}
 */


/**
 * @defgroup SDK_EVAL_I2C_Private_FunctionPrototypes                    SDK EVAL I2C Private Function Prototypes
 * @{
 */

/**
 * @}
 */


/**
 * @defgroup SDK_EVAL_I2C_Private_Functions                             SDK EVAL I2C Private Functions
 * @{
 */

/**
 * @}
 */



/**
 * @defgroup SDK_EVAL_I2C_Public_Functions                SDK EVAL I2C Public Functions
 * @{
 */



/**
 * @brief  Configures I2C interface
 * @param  baudrate I2C clock frequency
 * @retval SUCCESS in case of success, an error code otherwise
 */
ErrorStatus SdkEvalI2CInit(uint32_t baudrate)
{   
  GPIO_InitType GPIO_InitStructure;
  I2C_InitType I2C_InitStruct;
    
  /* Enable I2C and GPIO clocks */
  if(SDK_EVAL_I2C == I2C2) {
    SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO | CLOCK_PERIPH_I2C2, ENABLE);
  }
  else {
    SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO | CLOCK_PERIPH_I2C1, ENABLE);
  }
      
  /* Configure I2C pins */
  GPIO_InitStructure.GPIO_Pin = SDK_EVAL_I2C_CLK_PIN ;
  GPIO_InitStructure.GPIO_Mode = SDK_EVAL_I2C_CLK_MODE;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init(&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = SDK_EVAL_I2C_DATA_PIN;
  GPIO_InitStructure.GPIO_Mode = SDK_EVAL_I2C_DATA_MODE;  
  GPIO_Init(&GPIO_InitStructure);
      
  /* Configure I2C in master mode */
  I2C_StructInit(&I2C_InitStruct);
  I2C_InitStruct.I2C_OperatingMode = I2C_OperatingMode_Master;
  I2C_InitStruct.I2C_ClockSpeed = baudrate;
  I2C_Init((I2C_Type*)SDK_EVAL_I2C, &I2C_InitStruct);
  
  /* Clear all I2C pending interrupts */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MSK);
  
  return SUCCESS;
}


/**
 * @brief  I2C function to write registers of a slave device
 * @param  pBuffer buffer contains data to write
 * @param  DeviceAddr the I2C slave address
 * @param  RegisterAddr register address
 * @param  NumByteToRead number of byte to write
 * @retval SUCCESS in case of success, an error code otherwise
 */
ErrorStatus SdkEvalI2CWrite(uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t NumByteToWrite)
{
  I2C_TransactionType t;
  
  /* Write the slave address */
  t.Operation = I2C_Operation_Write;
  t.Address = DeviceAddr;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Enable;
  t.Length = 1+NumByteToWrite;
  
  /* Flush the slave address */
  I2C_FlushTx((I2C_Type*)SDK_EVAL_I2C);
  while (I2C_WaitFlushTx((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ONGOING);
  
  /* Begin transaction */
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);

  /* Fill TX FIFO with data to write */
  I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, RegisterAddr);

  for(uint8_t i=0; i<NumByteToWrite;i++) {
    I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, pBuffer[i]);
  }
  
  /* Wait loop */
  do {
    if(I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ABORTED)
      return ERROR;
   
  } while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD) == RESET);
    
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);

  return SUCCESS;
}

/**
 * @brief  I2C function to write registers of a slave device
 * @param  pBuffer buffer contains data to write
 * @param  DeviceAddr the I2C slave address
 * @param  RegisterAddr register address 16 bits
 * @param  NumByteToRead number of byte to write
 * @retval SUCCESS in case of success, an error code otherwise
 */
ErrorStatus SdkEvalI2CWrite16(uint8_t* pBuffer, uint8_t DeviceAddr, uint16_t RegisterAddr, uint8_t NumByteToWrite) {
	I2C_TransactionType t;

	/* Write the slave address */
	t.Operation = I2C_Operation_Write;
	t.Address = DeviceAddr;
	t.StartByte = I2C_StartByte_Disable;
	t.AddressType = I2C_AddressType_7Bit;
	t.StopCondition = I2C_StopCondition_Enable;
	t.Length = 2 + NumByteToWrite;

	/* Flush the slave address */
	I2C_FlushTx((I2C_Type*) SDK_EVAL_I2C);
	while (I2C_WaitFlushTx((I2C_Type*) SDK_EVAL_I2C) == I2C_OP_ONGOING);

	/* Begin transaction */
	I2C_BeginTransaction((I2C_Type*) SDK_EVAL_I2C, &t);

	/* Fill TX FIFO with data to write */
	I2C_FillTxFIFO((I2C_Type*) SDK_EVAL_I2C, (uint8_t)(RegisterAddr>>8));
	/* Fill TX FIFO with data to write */
	I2C_FillTxFIFO((I2C_Type*) SDK_EVAL_I2C, (uint8_t)(RegisterAddr));

	for (uint8_t i = 0; i < NumByteToWrite; i++) {
		I2C_FillTxFIFO((I2C_Type*) SDK_EVAL_I2C, pBuffer[i]);
	}

	/* Wait loop */
	do {
		if (I2C_GetStatus((I2C_Type*) SDK_EVAL_I2C) == I2C_OP_ABORTED)
		return ERROR;

	}while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD) == RESET);

	/* Clear pending bits */
	I2C_ClearITPendingBit((I2C_Type*) SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);

	return SUCCESS;
}


/**
 * @brief  I2C function to read registers from a slave device
 * @param  pBuffer buffer to retrieve data from a slave
 * @param  DeviceAddr the I2C slave address
 * @param  RegisterAddr register address
 * @param  NumByteToRead number of byte to read
 * @retval SUCCESS in case of success, an error code otherwise
 */
ErrorStatus SdkEvalI2CRead(uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t NumByteToRead)
{
  I2C_TransactionType t;
  
  /* Write the slave address */
  t.Operation = I2C_Operation_Write;
  t.Address = DeviceAddr;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Disable;
  t.Length = 1;  
  
  /* Flush the slave address */
  I2C_FlushTx((I2C_Type*)SDK_EVAL_I2C);
  while (I2C_WaitFlushTx((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ONGOING);
    
  /* Begin transaction */
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);
	
  /* Fill TX FIFO with data to write */
  I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, RegisterAddr);

  /* Wait loop */
  do {
    if(I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ABORTED)
      return ERROR;
    
  } while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS) == RESET);
  
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS);
  
  /* read data */
  t.Operation = I2C_Operation_Read;
  t.Address = DeviceAddr;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Enable;
  t.Length = NumByteToRead;  
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);
  
  /* Wait loop */
  do {
    if(I2C_OP_ABORTED == I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C))
      return ERROR;
    
  } while (RESET == I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD));
  
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);
  
  /* Get data from RX FIFO */
  while(NumByteToRead--) {
    *pBuffer = I2C_ReceiveData((I2C_Type*)SDK_EVAL_I2C);
    pBuffer ++;
  }
  
  return SUCCESS;
}


/**
 * @brief  I2C function to read registers from a slave device
 * @param  pBuffer buffer to retrieve data from a slave
 * @param  DeviceAddr the I2C slave address
 * @param  RegisterAddr register address in 16 bits
 * @param  NumByteToRead number of byte to read
 * @retval SUCCESS in case of success, an error code otherwise
 */
ErrorStatus SdkEvalI2CRead16(uint8_t* pBuffer, uint8_t DeviceAddr, uint16_t RegisterAddr, uint8_t NumByteToRead) {
	I2C_TransactionType t;

	/* Write the slave address */
	t.Operation = I2C_Operation_Write;
	t.Address = DeviceAddr;
	t.StartByte = I2C_StartByte_Disable;
	t.AddressType = I2C_AddressType_7Bit;
	t.StopCondition = I2C_StopCondition_Disable;
	t.Length = 2;

	/* Flush the slave address */
	I2C_FlushTx((I2C_Type*) SDK_EVAL_I2C);
	while (I2C_WaitFlushTx((I2C_Type*) SDK_EVAL_I2C) == I2C_OP_ONGOING);

	/* Begin transaction */
	I2C_BeginTransaction((I2C_Type*) SDK_EVAL_I2C, &t);

	/* Fill TX FIFO with data to write */
	I2C_FillTxFIFO((I2C_Type*) SDK_EVAL_I2C, (uint8_t)((RegisterAddr & 0xFF00)/256));
	I2C_FillTxFIFO((I2C_Type*) SDK_EVAL_I2C, (uint8_t)(RegisterAddr & 0x00FF));

	/* Wait loop */
	do {
		if (I2C_GetStatus((I2C_Type*) SDK_EVAL_I2C) == I2C_OP_ABORTED)
		return ERROR;

	}while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS) == RESET);

	/* Clear pending bits */
	I2C_ClearITPendingBit((I2C_Type*) SDK_EVAL_I2C, I2C_IT_MTDWS);

	/* read data */
	t.Operation = I2C_Operation_Read;
	t.Address = DeviceAddr;
	t.StartByte = I2C_StartByte_Disable;
	t.AddressType = I2C_AddressType_7Bit;
	t.StopCondition = I2C_StopCondition_Enable;
	t.Length = NumByteToRead;
	I2C_BeginTransaction((I2C_Type*) SDK_EVAL_I2C, &t);

	/* Wait loop */
	do {
		if (I2C_OP_ABORTED == I2C_GetStatus((I2C_Type*) SDK_EVAL_I2C))
		return ERROR;

	}while (RESET == I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD));

	/* Clear pending bits */
	I2C_ClearITPendingBit((I2C_Type*) SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);

	/* Get data from RX FIFO */
	while (NumByteToRead--) {
		*pBuffer = I2C_ReceiveData((I2C_Type*) SDK_EVAL_I2C);
		pBuffer ++;
	}

	return SUCCESS;
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



/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
