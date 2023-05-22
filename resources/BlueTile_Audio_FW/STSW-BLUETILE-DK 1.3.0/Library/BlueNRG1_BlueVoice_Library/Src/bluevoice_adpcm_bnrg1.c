/**
 ***************************************************************************************
 * File Name          : bluevoice_adpcm_bnrg1.c 
 * Author             : SRA
 * Version            : V1.0.0
 * Date               : September-2018
 * Description        : This file contains definitions for BlueVoice BlueNRG-1_2 profile.
 ****************************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "bluevoice_adpcm_bnrg1.h"
#include "timestamp_helper.h"

/** @addtogroup BV_ADPCM_BNRG1
 * @{
 */

/** @defgroup BV_ADPCM_BNRG1_Private_Includes
 * @{
 */

#ifdef BV_STREAM_COS
#include "math.h"
#endif
/**
 * @}
 */

/**
 * @brief BV_ADPCM_BNRG1_Handle structure definition
 */
typedef struct
{
  BV_Profile_Status ProfileState;                       /*!< Specifies the state of the BlueVoice Profile. */
  
  uint8_t configured;                                   /*!< Specifies if the BlueVoice Profile is configured or not. */
  
  uint8_t connected;                                    /*!< Specifies if the device is connected or not. */
  
  BV_Mode mode;                                         /*!< Specifies the current working modality: Not ready, Receiver, Transmitter, or Half Duplex. */
  
  uint16_t ConnectionHandle;                            /*!< Connection Handle. */

  uint16_t STATUS_timeutCount;                          /*!< Status timeout counter. */
  
  uint16_t STATUS_timeutValue;                          /*!< Status timeut value. */
  
  uint8_t AudioNotifEnabled;                            /*!< Audio characteristic enabled. */
  
  uint8_t AudioSyncNotifEnabled;                        /*!< Sync characteristic enabled. */

  BV_ADPCM_BNRG1_uuid_t BV_uuid;                        /*!< Specifies the uuid for the BlueVoice service and characteristics. */
  
  BV_ADPCM_BNRG1_ProfileHandle_t BV_handle;             /*!< Specifies the handle for the BlueVoice service and characteristics. */
  
  BV_ADPCM_BNRG1_ProfileHandle_t BV_handle_RX;          /*!< Specifies the handle for RX part in Half-Duplex application. */
  
  Sampling_fr_t sampling_frequency;                     /*!< Specifies the audio sampling frequency in kHz - can be 16 kHz or 8 kHz. */
  
  uint8_t channel_in;                                   /*!< The choosen channel among the available in the input buffer. */
        
  uint8_t channel_tot;                                  /*!< Number of audio channels contained in the buffer given as Audio input. */
  
  uint8_t ADPCMBuffSize;                                /*!< Size of the ADPCM buffer. */
    
  uint8_t ADPCMHalfBuffSize;                            /*!< Half size ADPCM buffer. */

  uint8_t OUTBuffSize;                                  /*!< Size of the Output buffer. */
    
  uint16_t ADPCMBuffCnt;                                /*!< ADPCM buffer counter. */
  
  uint32_t FrameCounter;                                /*!< Side information frame counter. */
    
  uint8_t ADPCMBuffReady;                               /*!< ADPCM Buffer status : 1=half buffer full, 2=complete buffer full. */
  
  uint8_t Nb_bytes_audio;                               /*!< Number of audio bytes to be sent. */
  
  uint8_t Nb_bytes_sync;                                /*!< Number of sync bytes to be sent. */
  
  uint8_t p_out_bytes;                                  /*!< Index of data to be sent. */
 
} BV_ADPCM_BNRG1_HandleTypeDef;

/**
  * @brief ADPCM handle Structure definition
  */
typedef struct
{
  int16_t index;                       /* Index */
  int32_t predsample;                  /* PredSample */
} BV_ADPCM_CodecHandleTypeDef;


/** @defgroup BV_ADPCM_BNRG1_Private_Constants
 * @{
 */


#ifdef BV_STREAM_COS
  #define COS_BUFF_SIZE_s16                             (160)
#endif
#define SIDE_INF_SIZE_u8                                (6)

/* BlueVoice can work with a connection interval of 10 or 20 ms */
#define CONN_INT_10
//#define CONN_INT_20

#ifdef CONN_INT_10
  #define SIDE_INF_FRAME_INTERVAL                         (16)
#endif

#ifdef CONN_INT_20
  #define SIDE_INF_FRAME_INTERVAL                         (8)
#endif


/**
 * @}
 */

/** @defgroup BV_ADPCM_BNRG1_Private_Macros
 * @{
 */
#ifndef MIN
  #define MIN(a,b)            ((a) < (b) )? (a) : (b)
#endif
/**
 * @}
 */

/** @defgroup BV_ADPCM_BNRG1_Private_Variables
 * @{
 */
static BV_ADPCM_BNRG1_HandleTypeDef hBV_ADPCM_BNRG1;

uint8_t timeStampOut[2];

#ifdef CONN_INT_10
  uint8_t BV_ADPCM_BNRG1_AudioIN_Buffer[160];
  uint8_t BV_ADPCM_BNRG1_AudioOUT_Buffer[86];
#endif
#ifdef CONN_INT_20 
  uint8_t BV_ADPCM_BNRG1_AudioIN_Buffer[320];
  uint8_t BV_ADPCM_BNRG1_AudioOUT_Buffer[166];
#endif

BV_ADPCM_CodecHandleTypeDef hBV_ADPCM_Encode, hBV_ADPCM_Decode;

static uint8_t ADPCM_sample[2];
#ifdef BV_STREAM_COS
  static int16_t cosine[COS_BUFF_SIZE_s16];
#endif
/**
 * @}
 */
 
/** @defgroup BV_ADPCM_BNRG1_Private_FunctionPrototypes
 * @{
 */

/**
 * @brief  This function is called to encode audio data.
 * @param  buffer_out: 8-bit packed ADPCM samples destination buffer.
 * @param  buffer_in: 16-bit PCM samples source buffer.
 * @param  Len: in data dimension in Bytes.
 * @retval AudioOUTLen: out data dimension in Bytes;
 */
static uint8_t BluevoiceADPCM_BNRG1_PrepareBuffOut(uint8_t* buffer_out, uint8_t* buffer_in, uint32_t Len);

/**
 * @brief  This function is called to write BV_ADPCM_BNRG1 Profile StateMachine status.
 * @param  State status to be written.
 * @retval None.
 */
static void BluevoiceADPCM_BNRG1_WriteStateMachine(BV_Profile_Status State);

/**
* @brief  This function is called to Encode 16-bit PCM sample to 4-bit ADPCM sample.
* @param  hBV_ADPCM_BNRG1_Codec: BlueVoice ADPCM handler.
* @param  sample: a 16-bit PCM sample
* @retval a 4-bit ADPCM sample
*/
static uint8_t BluevoiceADPCM_BNRG1_Encode(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, int32_t sample);

/**
* @brief  This function is called to Decode 4-bit ADPCM sample to 16-bit PCM sample.
* @param  hBV_ADPCM_BNRG1_Codec: BlueVoice ADPCM handler.
* @param  code: a byte containing a 4-bit ADPCM sample.
* @retval 16-bit ADPCM sample
*/
static int16_t BluevoiceADPCM_BNRG1_Decode(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, uint8_t code);

/**
* @brief  This function is called to apply synchronization mechanism.
* @param  hBV_ADPCM_BNRG1_Codec: BlueVoice ADPCM handler.
* @param  buffer: side information buffer.
* @retval None
*/
static void  BluevoiceADPCM_BNRG1_SyncIn(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, uint8_t* buffer);

/**
* @brief  This function is called to extrac sync information.
* @param  hBV_ADPCM_BNRG1_Codec: BlueVoice ADPCM handler.
* @param  buffer: side information buffer (dim: SIDE_INF_SIZE_u8).
* @retval None
*/
static void BluevoiceADPCM_BNRG1_SyncOut(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, uint8_t* buffer);

/**
* @brief  This function is called to reset ADPCM engine.
* @param  hBV_ADPCM_BNRG1_Codec: BlueVoice ADPCM handler.
* @retval None
*/
static void BluevoiceADPCM_BNRG1_Reset(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec);

/**
 * @}
 */

/** @defgroup BV_ADPCM_BNRG1_Exported_Functions
 * @{
 */

/**
  * @brief  This function is called to initialize the bluevoice library.
  * @param  None.
  * @retval None.
  */
void BluevoiceADPCM_BNRG1_Initialize(void)
{
  memset(&hBV_ADPCM_BNRG1, 0, sizeof(hBV_ADPCM_BNRG1));

  hBV_ADPCM_BNRG1.ProfileState = BLUEVOICE_STATUS_UNITIALIZED;
  hBV_ADPCM_BNRG1.mode = NOT_READY;
}

/**
  * @brief  This function is called to set the configuration parameters 
  * @param  BV_ADPCM_BNRG1_Config: It contains the configuration parameters.
  * @retval BV_BNRG1_Status: BV_SUCCESS if the configuration is ok, BV_ERROR otherwise.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_SetConfig(BV_ADPCM_BNRG1_Config_t *BV_ADPCM_BNRG1_Config)
{ 
  
#ifdef BV_STREAM_COS
  for(int i = 0; i < COS_BUFF_SIZE_s16; i++)
  {
    cosine[i] = (int16_t)(cos((2 * 3.14159265 * (1.0 / 16.0) * i)) * 10000.0); 
  }
#endif
  
  hBV_ADPCM_BNRG1.ProfileState = BLUEVOICE_STATUS_UNITIALIZED;
  hBV_ADPCM_BNRG1.FrameCounter = SIDE_INF_FRAME_INTERVAL-1;
  hBV_ADPCM_BNRG1.STATUS_timeutValue = BV_ADPCM_BNRG1_TIMEOUT_STATUS;
  hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
  hBV_ADPCM_BNRG1.ADPCMBuffCnt = 0;
  hBV_ADPCM_BNRG1.ADPCMBuffReady = 0;
  
  if(((BV_ADPCM_BNRG1_Config->channel_in > 0) && (BV_ADPCM_BNRG1_Config->channel_in <= BV_ADPCM_BNRG1_Config->channel_tot)) && ((BV_ADPCM_BNRG1_Config->channel_tot > 0) && (BV_ADPCM_BNRG1_Config->channel_tot < 9)))
  {
    hBV_ADPCM_BNRG1.channel_in = BV_ADPCM_BNRG1_Config->channel_in;
    hBV_ADPCM_BNRG1.channel_tot = BV_ADPCM_BNRG1_Config->channel_tot;
  }
  else
  {
    return BV_ERROR;
  }
   
  if((BV_ADPCM_BNRG1_Config->sampling_frequency == FR_8000) || (BV_ADPCM_BNRG1_Config->sampling_frequency == FR_16000))
  {
    hBV_ADPCM_BNRG1.sampling_frequency = BV_ADPCM_BNRG1_Config->sampling_frequency;

#ifdef CONN_INT_10    
    hBV_ADPCM_BNRG1.ADPCMBuffSize = (BV_ADPCM_BNRG1_Config->sampling_frequency/200)*2;  /* (FR/1000*10/4*2)*2 in byte, double buffer */
#endif    

#ifdef CONN_INT_20        
    hBV_ADPCM_BNRG1.ADPCMBuffSize = (BV_ADPCM_BNRG1_Config->sampling_frequency/100)*2;  /* (FR/1000*20/4*2)*2 in byte, double buffer */    
#endif
    hBV_ADPCM_BNRG1.ADPCMHalfBuffSize = hBV_ADPCM_BNRG1.ADPCMBuffSize/2;
    hBV_ADPCM_BNRG1.OUTBuffSize = hBV_ADPCM_BNRG1.ADPCMHalfBuffSize + SIDE_INF_SIZE_u8;
  }
  else
  {
    return BV_ERROR;
  }
  
  hBV_ADPCM_BNRG1.configured = 1;
  BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_INITIALIZED);
  return BV_SUCCESS; 
}

/**
  * @brief  This function returns if the BlueVoice Profile is configured.
  * @param  None.
  * @retval uint8_t: 1 if the profile is configured 0 otherwise.
  */
uint8_t BluevoiceADPCM_BNRG1_IsProfileConfigured(void)
{
  return hBV_ADPCM_BNRG1.configured;
}

/** 
  * @brief  This function is called to add BlueVoice Service.
  * @param  uuid: it contains service uuid value.
  * @param  service_handle: Pointer to a variable in which the service handle will be saved.
  * @retval BV_BNRG1_Status: Value indicating success or error code.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_AddService(BV_ADPCM_BNRG1_uuid_t *uuid, uint16_t *service_handle)
{
  uint8_t ret;

  if (hBV_ADPCM_BNRG1.configured)
  {
    memcpy(hBV_ADPCM_BNRG1.BV_uuid.service_uuid.Service_UUID_128,
                uuid->service_uuid.Service_UUID_128,
                sizeof(hBV_ADPCM_BNRG1.BV_uuid.service_uuid.Service_UUID_128));                 
                
    ret = aci_gatt_add_service(UUID_TYPE_128,
                            &hBV_ADPCM_BNRG1.BV_uuid.service_uuid, PRIMARY_SERVICE,  7,
                            &hBV_ADPCM_BNRG1.BV_handle.ServiceHandle); 
                               
    if (ret != BLE_STATUS_SUCCESS)
    {
      return BV_ERROR;
    }
    *service_handle = hBV_ADPCM_BNRG1.BV_handle.ServiceHandle;
    
    return BV_SUCCESS;    
  } 
  return BV_NOT_CONFIG;
}

/**
  * @brief  This function is called to add BlueVoice characteristics.
  * @param  uuid: It contains the uuid values of the Audio and audioSync characteristics.
  * @param  service_handle: Handle of the service to which the characteristic must be added.
  * @param  handle: Pointer to a BV_ADPCM_BNRG1_ProfileHandle_t struct in which the handles will be saved.
  * @retval BV_BNRG1_Status: BV_SUCCESS in case of success, BV_ERROR otherwise.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_AddChar(BV_ADPCM_BNRG1_uuid_t *uuid, uint16_t service_handle, BV_ADPCM_BNRG1_ProfileHandle_t *handle)
{
  tBleStatus ret;
  
  if (hBV_ADPCM_BNRG1.configured)
  {    
    handle->ServiceHandle = service_handle;
    hBV_ADPCM_BNRG1.BV_handle.ServiceHandle = service_handle;
    
    memcpy(hBV_ADPCM_BNRG1.BV_uuid.audio_uuid.Char_UUID_128,
                uuid->audio_uuid.Char_UUID_128,
                sizeof(hBV_ADPCM_BNRG1.BV_uuid.audio_uuid.Char_UUID_128));
    memcpy(hBV_ADPCM_BNRG1.BV_uuid.sync_uuid.Char_UUID_128,
                uuid->sync_uuid.Char_UUID_128,
                sizeof(hBV_ADPCM_BNRG1.BV_uuid.sync_uuid.Char_UUID_128));

#if defined(EXT_DATA_PCK) && defined(BLUENRG2_DEVICE)
    ret = aci_gatt_add_char(hBV_ADPCM_BNRG1.BV_handle.ServiceHandle,
                            UUID_TYPE_128, &hBV_ADPCM_BNRG1.BV_uuid.audio_uuid,
                            512, CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 16, 1,
                            &hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle);
#else
    ret = aci_gatt_add_char(hBV_ADPCM_BNRG1.BV_handle.ServiceHandle,
                            UUID_TYPE_128, &hBV_ADPCM_BNRG1.BV_uuid.audio_uuid,
                            22, CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 16, 1,
                            &hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle);
#endif
    
    if (ret != BLE_STATUS_SUCCESS)
    {
      return BV_ERROR;
    }
    handle->CharAudioHandle = hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle;    
      
      
    ret = aci_gatt_add_char(hBV_ADPCM_BNRG1.BV_handle.ServiceHandle,
                            UUID_TYPE_128,
                            &hBV_ADPCM_BNRG1.BV_uuid.sync_uuid, 6,
                            CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 16, 1,
                            &hBV_ADPCM_BNRG1.BV_handle.CharAudioSyncHandle);
                                
    if (ret != BLE_STATUS_SUCCESS)
    {
      return BV_ERROR;
    }
		
		handle->CharAudioSyncHandle = hBV_ADPCM_BNRG1.BV_handle.CharAudioSyncHandle;
		
    if (ret != BLE_STATUS_SUCCESS)
    {
      return BV_ERROR;
    }
		
    return BV_SUCCESS;
  } 
  return BV_NOT_CONFIG;
}

/**
  * @brief  This function is called to set the handles if the BlueVoice characteristics are added out of the library.
  * @param  tx_handle: Pointer to a BV_ADPCM_BNRG1_ProfileHandle_t struct in which the handles are stored.
  * @retval None.
  */
void BluevoiceADPCM_BNRG1_SetTxHandle(BV_ADPCM_BNRG1_ProfileHandle_t *tx_handle)
{
  hBV_ADPCM_BNRG1.BV_handle.ServiceHandle = tx_handle->ServiceHandle;
  hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle = tx_handle->CharAudioHandle;
  hBV_ADPCM_BNRG1.BV_handle.CharAudioSyncHandle = tx_handle->CharAudioSyncHandle;
}

/**
  * @brief  This function is called to set the handles discovered, if an other BlueVoice module is available.
  * @param  rx_handle: Pointer to a BV_ADPCM_BNRG1_ProfileHandle_t struct in which the handles are stored.
  * @retval None.
  */
void BluevoiceADPCM_BNRG1_SetRxHandle(BV_ADPCM_BNRG1_ProfileHandle_t *rx_handle)
{
  hBV_ADPCM_BNRG1.BV_handle_RX.ServiceHandle = rx_handle->ServiceHandle;
  hBV_ADPCM_BNRG1.BV_handle_RX.CharAudioHandle = rx_handle->CharAudioHandle;
  hBV_ADPCM_BNRG1.BV_handle_RX.CharAudioSyncHandle = rx_handle->CharAudioSyncHandle;
}

/**
  * @brief  This function returns the BlueVoice Profile State Machine status.
  * @param  None.
  * @retval BV_Profile_Status: BlueVoice Profile Status.
  */
BV_Profile_Status BluevoiceADPCM_BNRG1_GetStatus(void)
{
  return hBV_ADPCM_BNRG1.ProfileState;
}

/**
  * @brief  This function returns the current modality.
  * @param  None.
  * @retval BV_Mode: Current working modality: NOT_READY, RECEIVER, TRANSMITTER or HALF_DUPLEX.
  */
BV_Mode BluevoiceADPCM_BNRG1_GetMode(void)
{
  return hBV_ADPCM_BNRG1.mode;
}

/**
  * @brief  This function increases the the internal counter, used to switch from Receiving/Streaming to Ready status.
  * @param  None.
  * @retval BV_BNRG1_Status: Value indicating success or error code.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_IncTick(void)
{
  if(hBV_ADPCM_BNRG1.STATUS_timeutValue == 0)
  {
    return BV_ERROR;
  }

  if(hBV_ADPCM_BNRG1.ProfileState == BLUEVOICE_STATUS_RECEIVING)
  {
    hBV_ADPCM_BNRG1.STATUS_timeutCount++;
    if(hBV_ADPCM_BNRG1.STATUS_timeutCount == hBV_ADPCM_BNRG1.STATUS_timeutValue)
    {
      hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
      BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_READY);
    }
  }
  else if(hBV_ADPCM_BNRG1.ProfileState == BLUEVOICE_STATUS_STREAMING)
  {
    hBV_ADPCM_BNRG1.STATUS_timeutCount++;
    if(hBV_ADPCM_BNRG1.STATUS_timeutCount == hBV_ADPCM_BNRG1.STATUS_timeutValue)
    {
      hBV_ADPCM_BNRG1.FrameCounter = SIDE_INF_FRAME_INTERVAL-1;
      hBV_ADPCM_BNRG1.ADPCMBuffCnt = 0;
      hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
      BluevoiceADPCM_BNRG1_Reset(&hBV_ADPCM_Encode);
      BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_READY);
    }
  }
  return BV_SUCCESS;
}

/**
  * @brief  This function is called to enable Audio notification.
  * @param  None.
  * @retval BV_BNRG1_Status: Value indicating success or error code.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_EnableAudioNotification(void)
{
  uint8_t client_char_conf_data[] = { 0x01, 0x00 }; // Enable notifications
  
  if(aci_gatt_write_char_desc(hBV_ADPCM_BNRG1.ConnectionHandle,
                                  hBV_ADPCM_BNRG1.BV_handle_RX.CharAudioHandle + 2, 2,
                                  client_char_conf_data) == BLE_STATUS_NOT_ALLOWED)
  {
    return BV_ERROR;
  }
  
  if(hBV_ADPCM_BNRG1.mode == TRANSMITTER)
  {
    hBV_ADPCM_BNRG1.mode = HALF_DUPLEX;
  }
  else if(hBV_ADPCM_BNRG1.mode == NOT_READY)
  {
     hBV_ADPCM_BNRG1.mode = RECEIVER;
  }
  BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_READY);

  return BV_SUCCESS;
}

/**
  * @brief  This function is called to enable Sync notification.
  * @param  None.
  * @retval BV_BNRG1_Status: Value indicating success or error code.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_EnableSyncNotification(void)
{
  uint8_t client_char_conf_data[] = { 0x01, 0x00 }; // Enable notifications

  if(aci_gatt_write_char_desc(hBV_ADPCM_BNRG1.ConnectionHandle,
                                  hBV_ADPCM_BNRG1.BV_handle_RX.CharAudioSyncHandle + 2, 2,
                                  client_char_conf_data) == BLE_STATUS_NOT_ALLOWED)
  {
    return BV_ERROR;
  }

  if(hBV_ADPCM_BNRG1.mode == TRANSMITTER)
  {
    hBV_ADPCM_BNRG1.mode = HALF_DUPLEX;
  }
  else if(hBV_ADPCM_BNRG1.mode == NOT_READY)
  {
     hBV_ADPCM_BNRG1.mode = RECEIVER;
  }
  BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_READY);

  return BV_SUCCESS;
}

/**
  * @brief  This function is called to fill audio buffer.
  * @param  buffer: Audio in PCM buffer.
  * @param  Nsamples: Number of PCM 16 bit audio samples.
  * @retval BV_BNRG1_Status: Value indicating success or error code.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_AudioIn(uint16_t* buffer, uint8_t Nsamples)
{  
#ifdef BV_STREAM_COS
  static uint32_t cos_cnt = 0;
#endif
  
  if(!hBV_ADPCM_BNRG1.configured)
  {
    return BV_NOT_CONFIG;
  }
  
  if(!hBV_ADPCM_BNRG1.connected)
  {
    return BV_DISCONNETED;
  }
  
  if((hBV_ADPCM_BNRG1.mode != HALF_DUPLEX) && (hBV_ADPCM_BNRG1.mode != TRANSMITTER))
  {
    return BV_TRANSMITTER_DISABLE;
  }
   
  if(hBV_ADPCM_BNRG1.sampling_frequency == FR_16000)
  {
    if((Nsamples!=16)&&(Nsamples!=32)&&(Nsamples!=80)&&(Nsamples!=160))
    {
      return BV_PCM_SAMPLES_ERR;
    }
  }
  else if(hBV_ADPCM_BNRG1.sampling_frequency == FR_8000)
  {
#ifdef CONN_INT_10  
    if((Nsamples!=8)&&(Nsamples!=16)&&(Nsamples!=40)&&(Nsamples!=80))
#endif
#ifdef CONN_INT_20     
    if((Nsamples!=8)&&(Nsamples!=16)&&(Nsamples!=40)&&(Nsamples!=80)&&(Nsamples!=160))
#endif      
    {
      return BV_PCM_SAMPLES_ERR;
    }
  }
  else
  {
    return BV_ERROR;
  }
  
  /*-----------------------------------------compression---------------------------------------------------------*/
  
  for (uint32_t i = 0; i < Nsamples*hBV_ADPCM_BNRG1.channel_tot; i = i + 2 * hBV_ADPCM_BNRG1.channel_tot)
  {
  
#ifndef BV_STREAM_COS
    /* ADPCM_Encode voice */
    ADPCM_sample[0] = BluevoiceADPCM_BNRG1_Encode(&hBV_ADPCM_Encode, ((int16_t *) (buffer))[i + (hBV_ADPCM_BNRG1.channel_in-1)]);
    ADPCM_sample[1] = BluevoiceADPCM_BNRG1_Encode(&hBV_ADPCM_Encode, ((int16_t *) (buffer))[i + (hBV_ADPCM_BNRG1.channel_in-1) + hBV_ADPCM_BNRG1.channel_tot]);
#else
    ADPCM_sample[0] = BluevoiceADPCM_BNRG1_Encode(&hBV_ADPCM_Encode, (int16_t)cosine[cos_cnt]); // ADPCM_Encode cos
    cos_cnt++;
    cos_cnt %= COS_BUFF_SIZE_s16;
    ADPCM_sample[1] = BluevoiceADPCM_BNRG1_Encode(&hBV_ADPCM_Encode, (int16_t)cosine[cos_cnt]); // ADPCM_Encode cos
    cos_cnt++;
    cos_cnt %= COS_BUFF_SIZE_s16;
#endif
                         
    ((uint8_t *) (BV_ADPCM_BNRG1_AudioIN_Buffer))[hBV_ADPCM_BNRG1.ADPCMBuffCnt] = ADPCM_sample[0] & 0x0F;
    ((uint8_t *) (BV_ADPCM_BNRG1_AudioIN_Buffer))[hBV_ADPCM_BNRG1.ADPCMBuffCnt] |= (ADPCM_sample[1] << 4) & 0xF0;
    hBV_ADPCM_BNRG1.ADPCMBuffCnt++;
  }
  
  /*---------------------------------------------------------------------------------------------------------------*/
  
  if (hBV_ADPCM_BNRG1.ADPCMBuffCnt == hBV_ADPCM_BNRG1.ADPCMHalfBuffSize)
  {
    hBV_ADPCM_BNRG1.ADPCMBuffReady = 1;
    BluevoiceADPCM_BNRG1_PrepareBuffOut(BV_ADPCM_BNRG1_AudioOUT_Buffer,
                                   (uint8_t *) & (BV_ADPCM_BNRG1_AudioIN_Buffer[0]),
                                   hBV_ADPCM_BNRG1.ADPCMHalfBuffSize);
    
    hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
    BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_STREAMING);
    return BV_OUT_BUF_READY;
  }
  if (hBV_ADPCM_BNRG1.ADPCMBuffCnt == hBV_ADPCM_BNRG1.ADPCMBuffSize)
  {
    hBV_ADPCM_BNRG1.ADPCMBuffCnt = 0;
    hBV_ADPCM_BNRG1.ADPCMBuffReady = 2;
    BluevoiceADPCM_BNRG1_PrepareBuffOut(BV_ADPCM_BNRG1_AudioOUT_Buffer,
                         (uint8_t *) & (BV_ADPCM_BNRG1_AudioIN_Buffer[hBV_ADPCM_BNRG1.ADPCMHalfBuffSize]),
                          hBV_ADPCM_BNRG1.ADPCMHalfBuffSize);
    
    hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
    BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_STREAMING);
    return BV_OUT_BUF_READY;
  }
  return BV_OUT_BUF_NOT_READY;
}

/**
  * @brief  This function is called to parse received data.
  * @param  buffer_in: 8-bit packed ADPCM samples source buffer.
  * @param  Len: Dimension in Bytes.
  * @param  attr_handle: Handle of the updated characteristic.
  * @param  buffer_out: 16-bit PCM samples destination buffer.
  * @param  samples: Number of 16-bit PCM samples in the destination buffer.
  * @retval BV_BNRG1_Status: Value indicating success or error code.
  */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_ParseData(uint8_t* buffer_in, uint32_t Len, uint16_t attr_handle, uint8_t* buffer_out, uint8_t *samples)
{
  *samples = 0;
  
  if((hBV_ADPCM_BNRG1.mode == HALF_DUPLEX) || (hBV_ADPCM_BNRG1.mode == RECEIVER))
  {
    if (attr_handle == hBV_ADPCM_BNRG1.BV_handle_RX.CharAudioHandle + 1)
    {
      hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;   
      BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_RECEIVING);
        
      for (uint8_t i = 0; i < Len; i++)
      {
        ((int16_t *) (buffer_out))[2 * i] = (int16_t) BluevoiceADPCM_BNRG1_Decode(&hBV_ADPCM_Decode, (uint8_t) (buffer_in[i] & 0x0F));
        ((int16_t *) (buffer_out))[2 * i + 1] = (int16_t) BluevoiceADPCM_BNRG1_Decode(&hBV_ADPCM_Decode, (uint8_t) (buffer_in[i] >> 4) & 0x0F);
      }
      *samples = Len * 4 / 2;
      return BV_SUCCESS;
    }
    else if (attr_handle == hBV_ADPCM_BNRG1.BV_handle_RX.CharAudioSyncHandle + 1)
    {
      BluevoiceADPCM_BNRG1_SyncIn(&hBV_ADPCM_Decode, (uint8_t*) buffer_in);
      return BV_SUCCESS;
    }
    else
    {
      return BV_RX_HANDLE_NOT_AVAILABLE;
    }
  }
  else
  {
    return BV_RECEIVER_DISABLE;
  }
}
/**
 * @brief  This function is called to send data.
 * @param  None
 * @retval BV_BNRG1_Status: Value indicating success or error code.
 */
BV_BNRG1_Status BluevoiceADPCM_BNRG1_SendData(void)
{
  if(hBV_ADPCM_BNRG1.AudioNotifEnabled && hBV_ADPCM_BNRG1.AudioSyncNotifEnabled)
  {
    uint32_t len = 0;
    
    hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
    BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_STREAMING);
  
    
#if defined(EXT_DATA_PCK) && defined(BLUENRG2_DEVICE)
    if(aci_gatt_update_char_value_ext(hBV_ADPCM_BNRG1.ConnectionHandle, hBV_ADPCM_BNRG1.BV_handle.ServiceHandle, hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle, 0x01,
                                                   512, 0, hBV_ADPCM_BNRG1.Nb_bytes_audio, (uint8_t *) BV_ADPCM_BNRG1_AudioOUT_Buffer)==BLE_STATUS_INSUFFICIENT_RESOURCES)
    {
      return BV_INSUFFICIENT_RESOURCES;
    }
    hBV_ADPCM_BNRG1.p_out_bytes += hBV_ADPCM_BNRG1.Nb_bytes_audio;
    
#else
    while (hBV_ADPCM_BNRG1.p_out_bytes < hBV_ADPCM_BNRG1.Nb_bytes_audio)
    {
      len = MIN(20, hBV_ADPCM_BNRG1.Nb_bytes_audio - hBV_ADPCM_BNRG1.p_out_bytes);

      if(aci_gatt_update_char_value(hBV_ADPCM_BNRG1.BV_handle.ServiceHandle, hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle, 0,
                                    len, BV_ADPCM_BNRG1_AudioOUT_Buffer + hBV_ADPCM_BNRG1.p_out_bytes)==BLE_STATUS_INSUFFICIENT_RESOURCES)
      {
        return BV_INSUFFICIENT_RESOURCES;
      }
			
			updateTimestampCharacteristic();
    
      hBV_ADPCM_BNRG1.p_out_bytes += len;
    }
#endif  
    
    if(hBV_ADPCM_BNRG1.Nb_bytes_sync>0)
    {
      if(aci_gatt_update_char_value(hBV_ADPCM_BNRG1.BV_handle.ServiceHandle, hBV_ADPCM_BNRG1.BV_handle.CharAudioSyncHandle, 0, 6, (uint8_t *) BV_ADPCM_BNRG1_AudioOUT_Buffer + hBV_ADPCM_BNRG1.p_out_bytes)==BLE_STATUS_INSUFFICIENT_RESOURCES)
      {
        return BV_INSUFFICIENT_RESOURCES;
      }
    }   
    
    hBV_ADPCM_BNRG1.ADPCMBuffReady = 0;
    
    return BV_SUCCESS;
  }
  else
  {
    return BV_NOTIF_DISABLE; 
  }
}

/**
 * @}
 */

/** @defgroup BV_ADPCM_BNRG1_Private_Functions
 * @{
 */

/**
 * @brief  This function is called to write BLUEVOICE Profile StateMachine status.
 * @param  State status to be written.
 * @retval None.
 */
static void BluevoiceADPCM_BNRG1_WriteStateMachine(BV_Profile_Status State)
{
  hBV_ADPCM_BNRG1.ProfileState = State;
}

/**
 * @brief  This function is called to encode audio data.
 * @param  buffer_out: 8-bit packed ADPCM samples destination buffer.
 * @param  buffer_in: 16-bit PCM samples source buffer.
 * @param  Len: dimension in Bytes.
 * @retval buffer out size.
 */
static uint8_t BluevoiceADPCM_BNRG1_PrepareBuffOut(uint8_t* buffer_out, uint8_t* buffer_in, uint32_t Len)
{ 
  memcpy((uint8_t *) buffer_out, (uint8_t *) buffer_in, Len);
   
  hBV_ADPCM_BNRG1.FrameCounter++;
  
  if (hBV_ADPCM_BNRG1.FrameCounter == SIDE_INF_FRAME_INTERVAL)
  {
    hBV_ADPCM_BNRG1.FrameCounter = 0;
    BluevoiceADPCM_BNRG1_SyncOut(&hBV_ADPCM_Encode,
                            (uint8_t *) &buffer_out[Len]);
    hBV_ADPCM_BNRG1.Nb_bytes_audio = hBV_ADPCM_BNRG1.OUTBuffSize - SIDE_INF_SIZE_u8;
    hBV_ADPCM_BNRG1.Nb_bytes_sync = SIDE_INF_SIZE_u8;
    hBV_ADPCM_BNRG1.p_out_bytes = 0;
    return  hBV_ADPCM_BNRG1.OUTBuffSize;
  }
  else
  {
    memset((uint8_t *) &buffer_out[Len], 0, SIDE_INF_SIZE_u8);
    hBV_ADPCM_BNRG1.Nb_bytes_audio = hBV_ADPCM_BNRG1.OUTBuffSize - SIDE_INF_SIZE_u8;
    hBV_ADPCM_BNRG1.Nb_bytes_sync = 0;
    hBV_ADPCM_BNRG1.p_out_bytes = 0;
    return ( hBV_ADPCM_BNRG1.OUTBuffSize - SIDE_INF_SIZE_u8);
  }
}

/**
 * @}
 */

/** @defgroup BV_ADPCM_BNRG1_Exported_Callbacks
 * @{
 */

/**
  * @brief  This function must be called when there is a LE Connection Complete event.
  * @param  handle: Connection handle.
  * @retval None.
  */
void BluevoiceADPCM_BNRG1_ConnectionComplete_CB(uint16_t handle)
{
  hBV_ADPCM_BNRG1.ConnectionHandle = handle;
  hBV_ADPCM_BNRG1.connected = 1;
}

/**
  * @brief  This function must be called when there is a LE disconnection Complete event. 
  * @param  None.
  * @retval None.
  */
void BluevoiceADPCM_BNRG1_DisconnectionComplete_CB(void)
{
  BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_INITIALIZED);

  hBV_ADPCM_BNRG1.connected = 0;
  hBV_ADPCM_BNRG1.AudioNotifEnabled = 0;
  hBV_ADPCM_BNRG1.AudioSyncNotifEnabled = 0;
  hBV_ADPCM_BNRG1.ConnectionHandle = 0;
  hBV_ADPCM_BNRG1.ADPCMBuffCnt = 0;        
  hBV_ADPCM_BNRG1.FrameCounter = SIDE_INF_FRAME_INTERVAL-1; 
  hBV_ADPCM_BNRG1.ADPCMBuffReady = 0;
  hBV_ADPCM_BNRG1.STATUS_timeutCount = 0;
  hBV_ADPCM_BNRG1.mode = NOT_READY;
}

/**
  * @brief  This function must be called when there is a LE attribut modified event. 
  * @param  attr_handle: Attribute handle.
  * @param  attr_len: Attribute length.
  * @param  attr_value: Attribute value.
  * @retval None.
  */
void BluevoiceADPCM_BNRG1_AttributeModified_CB(uint16_t attr_handle, uint8_t attr_len, uint8_t *attr_value)
{
  if (attr_handle == hBV_ADPCM_BNRG1.BV_handle.CharAudioHandle + 2)
  {
    if (attr_value[0] == 0x01)
    {
      hBV_ADPCM_BNRG1.AudioNotifEnabled = 1;
      if(hBV_ADPCM_BNRG1.AudioSyncNotifEnabled)
      {
        if(hBV_ADPCM_BNRG1.mode == NOT_READY)
        {
          hBV_ADPCM_BNRG1.mode = TRANSMITTER;
        }
        else if(hBV_ADPCM_BNRG1.mode == RECEIVER)
        {
          hBV_ADPCM_BNRG1.mode = HALF_DUPLEX;
        }
        BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_READY);   
      }
    }
    else if(attr_value[0] == 0x00)
    {
      if(hBV_ADPCM_BNRG1.mode == TRANSMITTER)
      {
        hBV_ADPCM_BNRG1.mode = NOT_READY;
      }
      else if(hBV_ADPCM_BNRG1.mode == HALF_DUPLEX)
      {
        hBV_ADPCM_BNRG1.mode = RECEIVER;
      }
    }  
  }
  else if (attr_handle == hBV_ADPCM_BNRG1.BV_handle.CharAudioSyncHandle + 2)
  {
    if (attr_value[0] == 0x01)
    {
      hBV_ADPCM_BNRG1.AudioSyncNotifEnabled = 1;
      if(hBV_ADPCM_BNRG1.AudioNotifEnabled)
      {
        if(hBV_ADPCM_BNRG1.mode == NOT_READY)
        {
          hBV_ADPCM_BNRG1.mode = TRANSMITTER;
        }
        else if(hBV_ADPCM_BNRG1.mode == RECEIVER)
        {
          hBV_ADPCM_BNRG1.mode = HALF_DUPLEX;
        }
        BluevoiceADPCM_BNRG1_WriteStateMachine(BLUEVOICE_STATUS_READY);
      }
    }
    else if(attr_value[0] == 0x00)
    {
      if(hBV_ADPCM_BNRG1.mode == TRANSMITTER)
      {
        hBV_ADPCM_BNRG1.mode = NOT_READY;
      }
      else if(hBV_ADPCM_BNRG1.mode == HALF_DUPLEX)
      {
        hBV_ADPCM_BNRG1.mode = RECEIVER;
      }
    }     
  }
}

/**
 * @}
 */


/*-------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------ADPCM COMPRESSION/DECOMPRESSION---------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/

/* Quantizer step size lookup table */
static const uint16_t StepSizeTable[89] = {7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
                                           19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
                                           50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
                                           130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
                                           337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
                                           876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
                                           2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
                                           5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
                                           15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
                                          };
/* Table of index changes */
static const int8_t IndexTable[16] = {0xff, 0xff, 0xff, 0xff, 2, 4, 6, 8, 0xff, 0xff, 0xff, 0xff, 2, 4, 6, 8};

/**
* @brief  This function is called to Encode 16-bit PCM sample to 4-bit ADPCM sample.
* @param  hBV_ADPCM_BNRG1_Codec: BLUEVOICE ADPCM handler.
* @param  sample: a 16-bit PCM sample
* @retval a 4-bit ADPCM sample
*/
static uint8_t BluevoiceADPCM_BNRG1_Encode(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, int32_t sample)
{
  uint8_t code = 0;
  uint16_t tmpstep = 0;
  int32_t diff = 0;
  int32_t diffq = 0;
  uint16_t step = 0;
  
  step = StepSizeTable[hBV_ADPCM_BNRG1_Codec->index];
  
  /* 1. compute diff and record sign and absolut value */
  diff = sample - hBV_ADPCM_BNRG1_Codec->predsample;
  if (diff < 0)
  {
    code = 8;
    diff = -diff;
  }
  
  /* 2. quantize the diff into ADPCM code */
  /* 3. inverse quantize the code into a predicted diff */
  tmpstep = step;
  diffq = (step >> 3);
  
  
  if (diff >= tmpstep)
  {
    code |= 0x04;
    diff -= tmpstep;
    diffq += step;
  }
  
  tmpstep = tmpstep >> 1;
  
  
  if (diff >= tmpstep)
  {
    code |= 0x02;
    diff -= tmpstep;
    diffq += (step >> 1);
  }
  
  tmpstep = tmpstep >> 1;
  
  if (diff >= tmpstep)
  {
    code |= 0x01;
    diffq += (step >> 2);
  }
  
  /* 4. fixed predictor to get new predicted sample*/
  if (code & 8)
  {
    hBV_ADPCM_BNRG1_Codec->predsample -= diffq;
  }
  else
  {
    hBV_ADPCM_BNRG1_Codec->predsample += diffq;
  }
  
  
  /* check for overflow*/
  if (hBV_ADPCM_BNRG1_Codec->predsample > 32767)
  {
    hBV_ADPCM_BNRG1_Codec->predsample = 32767;
  }
  else if (hBV_ADPCM_BNRG1_Codec->predsample < -32768)
  {
    hBV_ADPCM_BNRG1_Codec->predsample = -32768;
  }
  
  /* 5. find new stepsize hBV_ADPCM_BNRG1_Codec->index */
  hBV_ADPCM_BNRG1_Codec->index += IndexTable[code];
  /* check for overflow*/
  if (hBV_ADPCM_BNRG1_Codec->index < 0)
  {
    hBV_ADPCM_BNRG1_Codec->index = 0;
  }
  else if (hBV_ADPCM_BNRG1_Codec->index > 88)
  {
    hBV_ADPCM_BNRG1_Codec->index = 88;
  }
  
   /* 6. return new ADPCM code*/
  return (code & 0x0f);
}

/**
* @brief  This function is called to Decode 4-bit ADPCM sample to 16-bit PCM sample.
* @param  hBV_ADPCM_BNRG1_Codec: BLUEVOICE ADPCM handler.
* @param  code: a byte containing a 4-bit ADPCM sample.
* @retval 16-bit ADPCM sample
*/
static int16_t BluevoiceADPCM_BNRG1_Decode(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, uint8_t code)
{
  uint16_t step = 0;
  int32_t diffq = 0;
  
  step = StepSizeTable[hBV_ADPCM_BNRG1_Codec->index];
  
  /* 1. inverse code into diff */
  diffq = step >> 3;
  if (code & 4)
  {
    diffq += step;
  }
  
  if (code & 2)
  {
    diffq += step >> 1;
  }
  
  if (code & 1)
  {
    diffq += step >> 2;
  }
  
  /* 2. add diff to predicted sample*/
  if (code & 8)
  {
    hBV_ADPCM_BNRG1_Codec->predsample -= diffq;
  }
  else
  {
    hBV_ADPCM_BNRG1_Codec->predsample += diffq;
  }
  
  /* check for overflow*/
  if (hBV_ADPCM_BNRG1_Codec->predsample > 32767)
  {
    hBV_ADPCM_BNRG1_Codec->predsample = 32767;
  }
  else if (hBV_ADPCM_BNRG1_Codec->predsample < -32768)
  {
    hBV_ADPCM_BNRG1_Codec->predsample = -32768;
  }
  
  /* 3. find new quantizer step size */
  hBV_ADPCM_BNRG1_Codec->index += IndexTable [code];
  /* check for overflow*/
  if (hBV_ADPCM_BNRG1_Codec->index < 0)
  {
    hBV_ADPCM_BNRG1_Codec->index = 0;
  }
  if (hBV_ADPCM_BNRG1_Codec->index > 88)
  {
    hBV_ADPCM_BNRG1_Codec->index = 88;
  }
  
  /* 4. return new speech sample*/
  return ((int16_t)hBV_ADPCM_BNRG1_Codec->predsample);
}

/**
* @brief  This function is called to apply synchronization mechanism.
* @param  hBV_ADPCM_BNRG1_Codec: BLUEVOICE ADPCM handler.
* @param  buffer: side information buffer.
* @retval None
*/
static void  BluevoiceADPCM_BNRG1_SyncIn(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, uint8_t* buffer)
{
  hBV_ADPCM_BNRG1_Codec->index = ((int16_t)buffer[0]) & 0x00FF;
  hBV_ADPCM_BNRG1_Codec->index |= ((int16_t)buffer[1] << 8) & 0xFF00;
  hBV_ADPCM_BNRG1_Codec->predsample = ((int32_t)buffer[2]) & 0x000000FF;
  hBV_ADPCM_BNRG1_Codec->predsample |= ((int32_t)buffer[3] << 8) & 0x0000FF00;
  hBV_ADPCM_BNRG1_Codec->predsample |= ((int32_t)buffer[4] << 16) & 0x00FF0000;
  hBV_ADPCM_BNRG1_Codec->predsample |= ((int32_t)buffer[5] << 24) & 0xFF000000;
}

/**
* @brief  This function is called to extrac sync information.
* @param  hBV_ADPCM_BNRG1_Codec: BLUEVOICE ADPCM handler.
* @param  buffer: side information buffer (dim: SIDE_INF_SIZE_u8).
* @retval None
*/
static void BluevoiceADPCM_BNRG1_SyncOut(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec, uint8_t* buffer)
{
  /*-------------------side information---------------------------------------*/
  buffer[0] = (hBV_ADPCM_BNRG1_Codec->index & 0x00FF);
  buffer[1] = (hBV_ADPCM_BNRG1_Codec->index >> 8) & 0x00FF;
  buffer[2] = (hBV_ADPCM_BNRG1_Codec->predsample & 0x000000FF);
  buffer[3] = (hBV_ADPCM_BNRG1_Codec->predsample >> 8) & 0x000000FF;
  buffer[4] = (hBV_ADPCM_BNRG1_Codec->predsample >> 16) & 0x000000FF;
  buffer[5] = (hBV_ADPCM_BNRG1_Codec->predsample >> 24) & 0x000000FF;
}

/**
* @brief  This function is called to reset ADPCM engine.
* @param  hBV_ADPCM_BNRG1_Codec: BLUEVOICE ADPCM handler.
* @retval None
*/
static void BluevoiceADPCM_BNRG1_Reset(BV_ADPCM_CodecHandleTypeDef *hBV_ADPCM_BNRG1_Codec)
{
  hBV_ADPCM_BNRG1_Codec->index = 0x0000;
  hBV_ADPCM_BNRG1_Codec->predsample = 0x00000000;
}

/**
* @}
*/


/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/

