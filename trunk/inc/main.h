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
#include "keyboard.h"

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

#define NEXT_TRACK	3
#define SEND_UART	1
#define PLAY_PAUSE	2
#define VOL_UP		6
#define	VOL_DOWN	4
#define BASS_UP		9
#define BASS_DOWN	7
#define TREBLE_UP	12
#define TREBLE_DOWN	10

#define SD_BlockSize           512

typedef enum {
	MP3_Player = 0,
	FM_Radio = 1,
	Main_Screen = 2,
	MP3_Player_1st_Run = 3,
	MP3_Player_Paused = 4
} System_Function;

void SD_Config();
void intToStr(char * string,int n);
void SD_Nvic_conf();
void clkInit();		// konfiguracja zegara
void pinSetup(); 	// konfiguracja portow
void Maintain_Player_Keyboard_Event(FIL* File, DIR* Directory, FILINFO* File_Info);
void Next_Track(FIL* File, DIR* Directory, FILINFO* File_Info);
//UART
void Send_Playback_Time();
void Send_Bitrate();
void Send_Samplerate();
void Send_Volume();
uint8_t IsPlayable(char* File_Name);
unsigned char showBit(__IO uint16_t Bytes, unsigned char bitNum);
#endif /* MAIN_H_ */
