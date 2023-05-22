/**
 * @file    LIS2MDL_HAL.h
 * @author  AMS VMA RF application team
 * @version V1.0.0
 * @date    September 29, 2015
 * @brief   This file provides all the low level API to manage LIS2MDL magnetometer sensor of eval board.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIS2MDL_HAL_H
#define __LIS2MDL_HAL_H

/* Includes ------------------------------------------------------------------*/
#include "SDK_EVAL_I2C.h"
#include "LIS2MDL.h"

#ifdef __cplusplus
extern "C" {
#endif

	/** @addtogroup SDK_EVAL_BlueNRG1 SDK EVAL BlueNRG1
	 * @{
	 */

	/** @addtogroup LIS2MDL            LIS2MDL
	 * @{
	 */

	/** @addtogroup SDK_EVAL_LIS2MDL_HAL            SDK EVAL LIS2MDL_HAL
	 * @{
	 */

	/** @defgroup SDK_EVAL_LIS2MDL_HAL_Exported_Types               SDK EVAL LIS2MDL_HAL Exported Types
	 * @{
	 */

	/**
	 * @}
	 */

	/** @defgroup SDK_EVAL_LIS2MDL_HAL_Exported_Constants                           SDK EVAL LIS2MDL_HAL Exported Constants
	 * @{
	 */

	/**
	 * @}
	 */

	/**
	 * @defgroup SDK_EVAL_LIS2MDL_HAL_Exported_Macros                       SDK EVAL LIS2MDL_HAL Exported Macros
	 * @{
	 */

	/**
	 * @}
	 */

	/** @defgroup SDK_EVAL_LIS2MDL_HAL_Exported_Functions                   SDK EVAL LIS2MDL_HAL Exported Functions
	 * @{
	 */

#define LIS2MDL_I2C_FREQUENCY           (100000)

#ifdef BLUENRG1_I2C_DMA

#define LIS2MDL_IO_Init()                                                       (int32_t)SdkEvalI2CDmaInit(LIS2MDL_I2C_FREQUENCY)
#define LIS2MDL_IO_Write(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)     (int32_t)SdkEvalI2CDmaWrite(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)
#define LIS2MDL_IO_Read(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)       (int32_t)SdkEvalI2CDmaRead(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)

#else
#ifdef BLUENRG1_I2C_IRQ

#define LIS2MDL_IO_Init()                                                       (int32_t)SdkEvalI2CIrqInit(LIS2MDL_I2C_FREQUENCY)
#define LIS2MDL_IO_Write(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)     (int32_t)SdkEvalI2CIrqWrite(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)
#define LIS2MDL_IO_Read(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)       (int32_t)SdkEvalI2CIrqRead(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)

#else /* BLUENRG1_I2C_POLL */

#define LIS2MDL_IO_Init()                                                       (int32_t)SdkEvalI2CInit(LIS2MDL_I2C_FREQUENCY)
#define LIS2MDL_IO_Write(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)     (int32_t)SdkEvalI2CWrite(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)
#define LIS2MDL_IO_Read(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)       (int32_t)SdkEvalI2CRead(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)

#endif /* BLUENRG1_I2C_IRQ */
#endif /* BLUENRG1_I2C_DMA */

#define LIS2MDL_IO_ITConfig()

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

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
