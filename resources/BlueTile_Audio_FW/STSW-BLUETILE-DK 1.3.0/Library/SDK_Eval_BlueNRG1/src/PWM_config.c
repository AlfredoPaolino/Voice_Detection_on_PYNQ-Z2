/**
********************************************************************************
* @file    PWM_config.c
* @author  BLE Mesh Team
* @version V1.0.0
* @date    31-July-2018
* @brief   Configuration file for PWM.
********************************************************************************
* @attention
*
*<h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
* Initial BlueNRG-Mesh is built over Motorola’s Mesh over Bluetooth Low Energy 
* (MoBLE) technology. The present solution is developed and maintained for both 
* Mesh library and Applications solely by STMicroelectronics.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "PWM_config.h"
#include "SDK_EVAL_Config.h"

 
/**
  *@brief  Configure PWM sources and GPIO
  *@retval None
  */
void PWM_Init() {
	
/* Prescaler for clock freqquency for MFT */	
#if (HS_SPEED_XTAL == HS_SPEED_XTAL_32MHZ)
	uint16_t prescaler = 16;
#elif (HS_SPEED_XTAL == HS_SPEED_XTAL_16MHZ)
	uint16_t prescaler = 8;
#endif
	
/* GPIO Configuration */
  GPIO_InitType GPIO_InitStructure;
   
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, ENABLE);

  /* Configure PWM pins */
  GPIO_InitStructure.GPIO_Pin = PWM0_PIN ;
  GPIO_InitStructure.GPIO_Mode = Serial2_Mode;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init( &GPIO_InitStructure);
  
   /* Configure PWM pins */
  GPIO_InitStructure.GPIO_Pin = PWM1_PIN;
  GPIO_InitStructure.GPIO_Mode = Serial1_Mode; //mode 1
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init( &GPIO_InitStructure);
  
  /* Configure GPIOs pin used to output PWM signal */
  GPIO_InitStructure.GPIO_Pin = PWM2_PIN | PWM3_PIN | PWM4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Output;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init( &GPIO_InitStructure);
	
  /* MFT Configuration */
  NVIC_InitType NVIC_InitStructure;
  MFT_InitType timer_init;
  
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_MTFX1 | CLOCK_PERIPH_MTFX2, ENABLE);
  
  MFT_StructInit(&timer_init);
  
  timer_init.MFT_Mode = MFT_MODE_1;  
  timer_init.MFT_Prescaler = prescaler - 1;      /* 2 MHz prescaled frequency*/
                                        
  /* MFT1 configuration */
  timer_init.MFT_Clock2 = MFT_PRESCALED_CLK;
  timer_init.MFT_Clock1 = MFT_PRESCALED_CLK;
  timer_init.MFT_CRA = MFT1_TON_1;       /* Capture/Reload A */
  timer_init.MFT_CRB = MFT1_TOFF_1;      /* Capture/Reload B */
  MFT_Init(MFT1, &timer_init);
  MFT_SetCounter2(MFT1, MFT1_TON_2);
  
  /* MFT2 configuration */
  timer_init.MFT_Clock2 = MFT_PRESCALED_CLK;
  timer_init.MFT_Clock1 = MFT_PRESCALED_CLK;
  timer_init.MFT_CRA = MFT2_TON_1;       /* Capture/Reload A */
  timer_init.MFT_CRB = MFT2_TOFF_1;      /* Capture/Reload B */
  MFT_Init(MFT2, &timer_init);
  MFT_SetCounter2(MFT2, MFT2_TON_2);
    
  /* Enable TIMER INTERRUPT 2 Interrupt 1 */
  NVIC_InitStructure.NVIC_IRQChannel = MFT1B_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = HIGH_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable TIMER INTERRUPT 2 Interrupt 2 */ 
  NVIC_InitStructure.NVIC_IRQChannel = MFT2B_IRQn;
  NVIC_Init(&NVIC_InitStructure);
  
  /** Enable the MFT interrupt */
  MFT_EnableIT(MFT1, MFT_IT_TND, ENABLE);  /* TIMER INTERRUPT 2, MFT1B */
  MFT_EnableIT(MFT2, MFT_IT_TND, ENABLE);  /* TIMER INTERRUPT 2, MFT2B */
	
  MFT_TnXEN(MFT1, MFT_TnA, ENABLE);
  MFT_TnXEN(MFT2, MFT_TnA, ENABLE);
    
  /* Start MFT timers */
  MFT_Cmd(MFT1, ENABLE);
  MFT_Cmd(MFT2, ENABLE);
 
}
