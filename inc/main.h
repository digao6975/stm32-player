/*
 * main.h
 *
 *  Created on: Mar 29, 2011
 *      Author: Witek
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "radio.h"
#include "vs1003.h"
#include "stm32f10x_it.h"
#include "sdcard.h"
#include "ff.h"
#include "diskio.h"
#include "integer.h"

//defnicje portu diod LED
#define LED1_PORT			GPIOB
#define LED23_PORT			GPIOD
#define FM_PORT				GPIOB
#define LED1_PORT_CLK		RCC_APB2Periph_GPIOB
#define LED23_PORT_CLK		RCC_APB2Periph_GPIOD
#define LED1_PIN			GPIO_Pin_5
#define LED2_PIN			GPIO_Pin_6
#define LED3_PIN			GPIO_Pin_3
#define FM_SCL_PIN			GPIO_Pin_10
#define FM_SDA_PIN			GPIO_Pin_11

#define SD_BlockSize           512

typedef enum {
	MP3_Player = 0,
	FM_Radio = 1,
	Main_Screen = 2
} System_Function;

void SD_Config();
void SD_Nvic_conf();
void clkInit();		// konfiguracja zegara
void pinSetup(); 	// konfiguracja portow

unsigned char showBit(__IO uint16_t Bytes, unsigned char bitNum);
#endif /* MAIN_H_ */
