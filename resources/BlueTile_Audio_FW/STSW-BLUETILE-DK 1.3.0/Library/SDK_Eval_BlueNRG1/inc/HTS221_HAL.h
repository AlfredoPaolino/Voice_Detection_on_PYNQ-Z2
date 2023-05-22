/**
 * @file    HTS221_HAL.h
 * @author  AMS VMA RF application team
 * @version V1.0.0
 * @date    September 29, 2015
 * @brief   This file provides all the low level API to manage HTS221 pressure sensor of eval board.
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
#ifndef __HTS221_HAL_H
#define __HTS221_HAL_H

/* Includes ------------------------------------------------------------------*/
#include "SDK_EVAL_I2C.h"
#include "HTS221.h"

#ifdef __cplusplus
extern "C" {
#endif

	/** @addtogroup SDK_EVAL_BlueNRG1 SDK EVAL BlueNRG1
	 * @{
	 */

	/** @addtogroup HTS221            HTS221
	 * @{
	 */

	/** @addtogroup SDK_EVAL_HTS221_HAL            SDK EVAL HTS221_HAL
	 * @{
	 */

	/** @defgroup SDK_EVAL_HTS221_HAL_Exported_Types               SDK EVAL HTS221_HAL Exported Types
	 * @{
	 */

	/**
	 * @}
	 */

	/** @defgroup SDK_EVAL_HTS221_HAL_Exported_Constants                           SDK EVAL HTS221_HAL Exported Constants
	 * @{
	 */

	/**
	 * @}
	 */

	/**
	 * @defgroup SDK_EVAL_HTS221_HAL_Exported_Macros                       SDK EVAL HTS221_HAL Exported Macros
	 * @{
	 */

	/**
	 * @}
	 */

	/** @defgroup SDK_EVAL_HTS221_HAL_Exported_Functions                   SDK EVAL HTS221_HAL Exported Functions
	 * @{
	 */

#define HTS221_I2C_FREQUENCY           (100000)

#ifdef BLUENRG1_I2C_DMA

#define HTS221_IO_Init()                                                       (HTS221_Error_et)SdkEvalI2CDmaInit(HTS221_I2C_FREQUENCY)
#define HTS221_IO_Write(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)     (HTS221_Error_et)SdkEvalI2CDmaWrite(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)
#define HTS221_IO_Read(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)       (HTS221_Error_et)SdkEvalI2CDmaRead(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)

#else
#ifdef BLUENRG1_I2C_IRQ

#define HTS221_IO_Init()                                                       (HTS221_Error_et)SdkEvalI2CIrqInit(HTS221_I2C_FREQUENCY)
#define HTS221_IO_Write(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)     (HTS221_Error_et)SdkEvalI2CIrqWrite(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)
#define HTS221_IO_Read(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)       (HTS221_Error_et)SdkEvalI2CIrqRead(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)

#else /* BLUENRG1_I2C_POLL */

#define HTS221_IO_Init()                                                       (HTS221_Error_et)SdkEvalI2CInit(HTS221_I2C_FREQUENCY)
#define HTS221_IO_Write(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)     (HTS221_Error_et)SdkEvalI2CWrite(pBuffer, DeviceAddr, RegisterAddr, NumByteToWrite)
#define HTS221_IO_Read(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)       (HTS221_Error_et)SdkEvalI2CRead(pBuffer, DeviceAddr, RegisterAddr, NumByteToRead)

#endif /* BLUENRG1_I2C_IRQ */
#endif /* BLUENRG1_I2C_DMA */

#define HTS221_IO_ITConfig()

void HTTS221_HAL_SPI_Init(void);
HTS221_Error_et HAL_ReadReg(uint8_t reg_addr, uint8_t num_regs, uint8_t* buffer);
HTS221_Error_et HAL_WriteReg(uint8_t reg_addr, uint8_t num_regs, uint8_t* buffer);


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
