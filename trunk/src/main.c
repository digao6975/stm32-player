
/* Includes */
#include <stddef.h>
#include "stm32f10x.h"
#include "main.h"


SD_CardInfo SDCardInfo;
SD_Error Status = SD_OK;
BYTE buffer[1024]; // file copy buffer

System_Function State = MP3_Player;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	char path[50]={""};
	int i;
	FATFS fs;            		// Work area (file system object) for logical drive
    FIL fsrc, fdst;      		// file objects

    FRESULT res;         		// FatFs function common result code
    UINT br, bw;         		// File R/W count
    FILINFO finfo;
    DIR dirs;
    UINT bytes_saved;

    uint16_t VOL;

	clkInit();
	pinSetup();

	VS1003_GPIO_conf();
	VS1003_SPI_conf();
	//VS1003_SoftwareReset();
	VS1003_Start();

	SD_Nvic_conf();
	SD_Config();

	//temporary
	disk_initialize(0);
	res = f_mount(0, &fs);
	res = f_opendir(&dirs, path);
	//res = f_open(&fdst, "test.txt", FA_CREATE_ALWAYS);
	//res = f_close(&fdst);
	res = f_open(&fsrc, "test.mp3", FA_READ);
	//res = f_write(&fdst,"testuje",7,&bytes_saved);
	//res = f_close(&fdst);
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//SysTick_Config(9000000);
	while (1)
	{
		if ( State == MP3_Player )
		{
			VOL = ReadRegister(SPI_VOL);
			while(f_read(&fsrc, buffer, sizeof(buffer), &br) == 0)
			{
			SCI_ChipSelect(RESET);
			SDI_ChipSelect(SET);
			for (i=0;i<br;i++)
			{
				while(GPIO_ReadInputDataBit(DREQ_PORT,DREQ_PIN) == 0);
				SPIPutChar(buffer[i]);
			}
			/*
			res = f_read(&fsrc, buffer, sizeof(buffer), &br);
			if (res == 0 && br != 0 )
			VS1003_SendMusicBytes(buffer,br);
			else
				break;
			*/
			}
		}

	}
}


void clkInit() {
	/* Konfiguracja zegara */

	/* Reset RCC (na wszelki wypadek) */
	RCC_DeInit();

	/* W³¹czenie HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Oczekiwanie na gotowoœæ HSE */
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET) {
	}

	/* W³¹czenie opóŸnieñ dla FLASH */
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);

	/* HCLK = SYSCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	/* PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config(RCC_HCLK_Div2);

	/* PLLCLK = 8MHz * 9 = 72 MHz */
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

	/* W³¹czenie PLL */
	RCC_PLLCmd(ENABLE);

	/* Oczekiwanie na gotowoœæ PLL */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {
	}

	/* Wybór PLL na zegar systemowy */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	/* Oczekiwanie na wybór zegara systemowego */
	while (RCC_GetSYSCLKSource() != 0x08) {
	}
}

void pinSetup() {
	GPIO_InitTypeDef GPIO_InitStruct;

	// wlaczenie zegara dla GPIO
	RCC_APB2PeriphClockCmd(LED1_PORT_CLK | LED23_PORT_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	// konfiguracja pinów
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Pin = LED1_PIN;
	GPIO_Init(LED1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LED2_PIN | LED3_PIN;
	GPIO_Init(LED23_PORT, &GPIO_InitStruct);

}

void SD_Nvic_conf(){
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;					  //ÅäÖÃSDIOÖÐ¶ÏÔ´
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void SD_Config(void){
	  Status = SD_Init();

	  if (Status == SD_OK)
	  {
	    /*----------------- Read CSD/CID MSD registers ------------------*/
	    Status = SD_GetCardInfo(&SDCardInfo);
	  }

	  if (Status == SD_OK)
	  {
	    /*----------------- Select Card --------------------------------*/
	    Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
	  }

	  if (Status == SD_OK)
	  {
	    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
	  }

	  /* Set Device Transfer Mode to DMA */
	  if (Status == SD_OK)
	  {
	    Status = SD_SetDeviceMode(SD_DMA_MODE);//oet
	 //   Status = SD_SetDeviceMode(SD_POLLING_MODE);
	   // Status = SD_SetDeviceMode(SD_INTERRUPT_MODE);
	  }
}

//Najmniej znaczacy ma numer 0
unsigned char showBit(__IO uint16_t Bytes, unsigned char bitNum){
	return ((Bytes & (1 << bitNum) )>> bitNum);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 *
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 *
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
*/
#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */

