#include "stm32f10x.h"

#define FM_WRITE_ADDRESS	0b11000000


void init_i2c(void);
void init_NVIC_out();		// konfiguracja NVIC
void init_DMA_out();	// konfiguracja DMA1_14 do wysylania
void init_DMA_in();		// konfiguracja DMA1_15 do czytania

void sendData();
