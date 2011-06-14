/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "main.h"
#include "sdcard.h"
#include "keyboard.h"

extern void TimingDelay_Decrement(void);

/** @addtogroup Interrupt_Handlers
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

void I2C2_ER_IRQHandler(void){
	uint16_t sr1,sr2;
	sr1 = I2C_ReadRegister(I2C2,I2C_Register_SR2);
	sr2 = I2C_ReadRegister(I2C2,I2C_Register_SR1);
}

void TIM2_IRQHandler(){

	if (TIM_GetITStatus(TIM2,TIM_IT_CC1))
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
		TIM_ITConfig(TIM2, TIM_IT_CC1, DISABLE);
		TIM_Cmd(TIM2,DISABLE);
		Keyboard_Test_ROW(ROW1);
	}
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC2))
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
		TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE);
		TIM_Cmd(TIM2,DISABLE);
		Keyboard_Test_ROW(ROW2);
	}
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC3))
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);
		TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE);
		TIM_Cmd(TIM2,DISABLE);
		Keyboard_Test_ROW(ROW3);
	}
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC4))
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC4);
		TIM_ITConfig(TIM2, TIM_IT_CC4, DISABLE);
		TIM_Cmd(TIM2,DISABLE);
		Keyboard_Test_ROW(ROW4);
	}
	Keyboard_Set_All_Columns();
	EXTI_ClearFlag(EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5 );
}
/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void SDIO_IRQHandler(void)
{
	/* Process All SDIO Interrupt Sources */
	SD_ProcessIRQSrc();
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
 * Handler for ROW1 of matrix keyboard
 */
void EXTI2_IRQHandler(){
	if (EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
		EXTI_ClearFlag(EXTI_Line2);
		TIM_SetCompare1(TIM2, 100); // 100 * [1/(72MHz / 36 000)] = 50ms
		Keyboard_Timer_Start();
		TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
	}
}
/**
 * Handler for ROW2 of matrix keyboard
 */
void EXTI3_IRQHandler(){
	if (EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line3);
		EXTI_ClearFlag(EXTI_Line3);
		TIM_SetCompare2(TIM2, 100); // 100 * [1/(72MHz / 36 000)] = 50ms
		Keyboard_Timer_Start();
		TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	}
}
/**
 * Handler for ROW3 of matrix keyboard
 */
void EXTI4_IRQHandler(){
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		EXTI_ClearFlag(EXTI_Line4);
		TIM_SetCompare3(TIM2, 100); // 100 * [1/(72MHz / 36 000)] = 50ms
		Keyboard_Timer_Start();
		TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
	}
}
/**
 * Handler for ROW4 of matrix keyboard
 */
void EXTI9_5_IRQHandler(){
	if (EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearFlag(EXTI_Line5);
		TIM_SetCompare4(TIM2, 100); // 100 * [1/(72MHz / 36 000)] = 50ms
		Keyboard_Timer_Start();
		TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
	}
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
