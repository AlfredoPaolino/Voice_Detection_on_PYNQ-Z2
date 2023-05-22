/**
 * @file    SDK_EVAL_I2C.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SDK_EVAL_I2C_H
#define __SDK_EVAL_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_x_device.h"
#include "BlueNRG1_conf.h"
#include "SDK_EVAL_Config.h"
   
#ifdef __cplusplus
 extern "C" {
#endif


/** @addtogroup SDK_EVAL_BlueNRG1       SDK EVAL BlueNRG1
 * @{
 */

/** @addtogroup SDK_EVAL_I2C            SDK EVAL I2C
 * @{
 */

/** @defgroup SDK_EVAL_I2C_Exported_Types               SDK EVAL I2C Exported Types
 * @{
 */

/**
 * @}
 */


/** @defgroup SDK_EVAL_I2C_Exported_Constants             SDK EVAL I2C Exported Constants
 * @{
 */


/**
 * @brief  I2C buffer max size
 */
#define I2C_BUFF_SIZE                   (10)


/**
 * @}
 */

/**
 * @defgroup SDK_EVAL_I2C_Exported_Macros                       SDK EVAL I2C Exported Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup SDK_EVAL_I2C_Exported_Functions                   SDK EVAL I2C Exported Functions
 * @{
 */

 ErrorStatus SdkEvalI2CInit(uint32_t baudrate);
 ErrorStatus SdkEvalI2CWrite(uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t NumByteToWrite);
 ErrorStatus SdkEvalI2CWrite16(uint8_t* pBuffer, uint8_t DeviceAddr, uint16_t RegisterAddr, uint8_t NumByteToWrite);
 ErrorStatus SdkEvalI2CRead(uint8_t* pBuffer, uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t NumByteToRead);
 ErrorStatus SdkEvalI2CRead16(uint8_t* pBuffer, uint8_t DeviceAddr, uint16_t RegisterAddr, uint8_t NumByteToRead);

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
